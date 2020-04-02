.. _conn_read:

连接读取报文数据
-----------------------

.. code-block:: c

    /* read packet */
    static int iotx_mc_read_packet(iotx_mc_client_t *c, iotx_time_t *timer, unsigned int *packet_type)
    {
        MQTTHeader header = {0};
        int len = 0;
        int rem_len = 0;
        int rc = 0;
        unsigned int left_t = 0;

        if (!c || !timer || !packet_type) {
            return FAIL_RETURN;
        }
        HAL_MutexLock(c->lock_read_buf);
        rc = _alloc_recv_buffer(c, 0);
        if (rc < 0) {
            HAL_MutexUnlock(c->lock_read_buf);
            return FAIL_RETURN;
        }
        /* 1. read the header byte.  This has the packet type in it */
        left_t = iotx_time_left(timer);
        left_t = (left_t == 0) ? 1 : left_t;
        rc = c->ipstack->read(c->ipstack, c->buf_read, 1, left_t); //读取一个字节
        if (0 == rc) { /* timeout */
            *packet_type = 0;
            HAL_MutexUnlock(c->lock_read_buf);
            return SUCCESS_RETURN;
        } else if (1 != rc) {
            mqtt_debug("mqtt read error, rc=%d", rc);
            HAL_MutexUnlock(c->lock_read_buf);
            return FAIL_RETURN;
        }

``c->ipstack->read`` 赋值为 ``utils_net_read``
初始化位置：
``rc = iotx_net_init(pClient->ipstack, pInitParams->host, pInitParams->port, pInitParams->pub_key);``
根据宏配置和是否配置证书，选择是否使用ssl，
read_tcp(pNetwork, buffer, len, timeout_ms)
或
read_ssl(pNetwork, buffer, len, timeout_ms);


.. code-block:: c

        len = 1;

        /* 2. read the remaining length.  This is variable in itself */
        left_t = iotx_time_left(timer);
        left_t = (left_t == 0) ? 1 : left_t;
        if ((rc = iotx_mc_decode_packet(c, &rem_len, left_t)) < 0)  //继续读取，直到读取完长度字段
        {
            mqtt_err("decodePacket error,rc = %d", rc);
            HAL_MutexUnlock(c->lock_read_buf);
            return rc;
        }

        len += MQTTPacket_encode((unsigned char *)c->buf_read + 1,
                                rem_len); /* put the original remaining length back into the buffer */

        rc = _alloc_recv_buffer(c, rem_len + len);
        if (rc < 0) {
            HAL_MutexUnlock(c->lock_read_buf);
            return FAIL_RETURN;
        }

        /* Check if the received data length exceeds mqtt read buffer length */
        if ((rem_len > 0) && ((rem_len + len) > c->buf_size_read)) {
            mqtt_err("mqtt read buffer is too short, mqttReadBufLen : %u, remainDataLen : %d", c->buf_size_read, rem_len);
            
            /* drop data whitch over the length of mqtt buffer */
            //...buffer size不够的处理
            return SUCCESS_RETURN;
        }

        /* 3. read the rest of the buffer using a callback to supply the rest of the data */
        left_t = iotx_time_left(timer);
        left_t = (left_t == 0) ? 1 : left_t;
        if (rem_len > 0 && (c->ipstack->read(c->ipstack, c->buf_read + len, rem_len, left_t) != rem_len)) {
            mqtt_err("mqtt read error");
            HAL_MutexUnlock(c->lock_read_buf);
            return FAIL_RETURN;
        }

        header.byte = c->buf_read[0];
        *packet_type = header.bits.type;
        if ((len + rem_len) < c->buf_size_read) {
            c->buf_read[len + rem_len] = '\0';
        }
        HAL_MutexUnlock(c->lock_read_buf);
        return SUCCESS_RETURN;
    }