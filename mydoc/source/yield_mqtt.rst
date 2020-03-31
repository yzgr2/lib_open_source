.. _yield_mqtt:

连接 yield_func 
-------------------

.. code-block:: c

    static int _mqtt_yield(uint32_t timeout)
    {
        POINTER_SANITY_CHECK(_mqtt_conncection, NULL_VALUE_ERROR);

        return IOT_MQTT_Yield(_mqtt_conncection->context, timeout);
    }

    int IOT_MQTT_Yield(void *handle, int timeout_ms)
    {
        int                 rc = SUCCESS_RETURN;
        iotx_time_t         time;

        iotx_mc_client_t *pClient = (iotx_mc_client_t *)(handle ? handle : g_mqtt_client);

        POINTER_SANITY_CHECK(pClient, NULL_VALUE_ERROR);
        if (timeout_ms < 0) {
            mqtt_err("Invalid argument, timeout_ms = %d", timeout_ms);
            return -1;
        }
        if (timeout_ms == 0) {
            timeout_ms = 10;
        }

        iotx_time_init(&time);
        utils_time_countdown_ms(&time, timeout_ms);

        do {
            if (SUCCESS_RETURN != rc) {
                mqtt_err("error occur rc=%d", rc);
            }

            HAL_MutexLock(pClient->lock_yield); // yield函数加锁

            /* Keep MQTT alive or reconnect if connection abort */
            iotx_mc_keepalive(pClient); //处理心跳和重连

            /* acquire package in cycle, such as PINGRESP or PUBLISH */
            rc = iotx_mc_cycle(pClient, &time);
            if (SUCCESS_RETURN == rc) {
                /* check list of wait subscribe(or unsubscribe) ACK to remove node that is ACKED or timeout */
                MQTTSubInfoProc(pClient);   //清理已确认的publish消息，已超时的publish重发。
            }
            HAL_MutexUnlock(pClient->lock_yield);
            /*  */
            unsigned int left_t = iotx_time_left(&time);
            if (left_t < 10) {
                HAL_SleepMs(left_t); //睡眠
            } else {
                HAL_SleepMs(10);    //睡眠10ms，再次循环
            }
        } while (!utils_time_is_expired(&time));

        return 0;
    }

``iotx_mc_cycle`` 处理远程broker发过来的报文

.. code-block:: c

    /* MQTT cycle to handle packet from remote broker */
    static int iotx_mc_cycle(iotx_mc_client_t *c, iotx_time_t *timer)
    {
        iotx_mc_state_t state = iotx_mc_get_client_state(c);
        if (state != IOTX_MC_STATE_CONNECTED) {
            mqtt_debug("state = %d", state);
            return MQTT_STATE_ERROR;
        }

        /* read the socket, see what work is due */
        rc = iotx_mc_read_packet(c, timer, &packetType);
        if (rc != SUCCESS_RETURN) {
            HAL_MutexLock(c->lock_read_buf)
            _reset_recv_buffer(c);
            HAL_MutexUnlock(c->lock_read_buf);

            iotx_mc_set_client_state(c, IOTX_MC_STATE_DISCONNECTED); //设置状态
            mqtt_debug("readPacket error,result = %d", rc);
            return MQTT_NETWORK_ERROR;
        }

        switch (packetType) {
            case CONNACK: {
                mqtt_debug("CONNACK");
                break;
            case PUBACK: {
                mqtt_debug("PUBACK");
                    //实际处理：待确认列表中找到消息，设置状态为IOTX_MC_NODE_STATE_INVALID     
                    //由外层的MQTTSubInfoProc（）进行实际删除           
                    //如果应用层设置了回调，则调用 _handle_event(&c->handle_event, c, &msg)
                rc = iotx_mc_handle_recv_PUBACK(c);  
                if (SUCCESS_RETURN != rc) {
                    mqtt_err("recvPubackProc error,result = %d", rc);
                }

                break;
            }
            case SUBACK: {
                mqtt_debug("SUBACK");
                rc = iotx_mc_handle_recv_SUBACK(c);
                if (SUCCESS_RETURN != rc) {
                    mqtt_err("recvSubAckProc error,result = %d", rc);
                }
                break;
            }
            case PUBLISH: {
                mqtt_debug("PUBLISH");
                /* HEXDUMP_DEBUG(c->buf_read, 32); */

                rc = iotx_mc_handle_recv_PUBLISH(c);
                if (SUCCESS_RETURN != rc) {
                    mqtt_err("recvPublishProc error,result = %d", rc);
                }
                break;
            }
            //其他类型...
    }