.. _main:

主循环
-------------

sample.c 为例，sample函数主体:


.. code-block:: c

    int app_linkkit_sample(void)
    {    
        /* callback function saved to g_impl_event_map[evt] list */
        IOT_RegisterCallback(ITE_PROPERTY_SET, user_property_set_event_handler);  
        IOT_RegisterCallback(ITE_PROPERTY_GET, user_property_get_event_handler);
        IOT_RegisterCallback(ITE_REPORT_REPLY, user_report_reply_event_handler);

        app_context.device_id = IOT_Linkkit_Open(IOTX_LINKKIT_DEV_TYPE_MASTER, &device_meta_info);

        /* Start Connect AliCloud Server */
        res = IOT_Linkkit_Connect(app_context.device_id);
        if (res < 0) {
            APP_TRACE("IOT_Linkkit_Connect Failed");
            return -1;
        }
        APP_TRACE("IOT_Linkkit_Connect successfully");

        APP_TRACE("Linkkit enter loop");    //大循环
        while (1) {
            IOT_Linkkit_Yield(USER_EXAMPLE_YIELD_TIMEOUT_MS);

            now = app_uptime_sec();
            if (prev_sec == now) {
                continue;
            }

            /* post all properties every 5 second */
            if (now % 5 == 0) {
                app_post_all_property();
            }

            /* after all, this is an sample, give a chance to return... */
            /* modify this value for this sample executaion time period */
            if (now > 60 * SAMPLE_EXECUTION_TIME) {
                APP_TRACE("sample run timeout, break form loop");
                break;
            }
            prev_sec = now;
        }
    } 

USER_EXAMPLE_YIELD_TIMEOUT_MS 在demo中配置为200ms

``IOT_Linkkit_Yield`` 函数为sdk中的事件检测与处理轮询函数，处理完sdk中的时间后，每5秒post一次所有属性（模拟用户层应用）

.. code-block:: c

    void IOT_Linkkit_Yield(int timeout_ms)
    {
        iotx_linkkit_ctx_t *ctx = _iotx_linkkit_get_ctx();

        if (timeout_ms <= 0) {
            sdk_err("Invalid Parameter");
            return;
        }

        if (ctx->is_opened == 0 || ctx->is_connected == 0) {
            return;
        }

        iotx_dm_yield(timeout_ms);
        iotx_dm_dispatch();

    #if (CONFIG_SDK_THREAD_COST == 1)
        HAL_SleepMs(timeout_ms);
    #endif
    }

    int iotx_dm_yield(int timeout_ms)
    {
        if (timeout_ms <= 0) {
            return DM_INVALID_PARAMETER;
        }

        dm_client_yield(timeout_ms);   

        return SUCCESS_RETURN;
    }

    int dm_client_yield(unsigned int timeout)
    {
        dm_client_ctx_t *ctx = dm_client_get_ctx();

        return iotx_cm_yield(ctx->fd, timeout);
    }
  
``IOT_Linkkit_Yield`` 最终调用的是 ``_iotx_cm_yield`` 和 ``iotx_dm_dispatch``， 进行事件的轮询和处理.
实际调用的是个mqtt或coap连接的yeild函数， 如 ``_mqtt_yield``。 

.. code-block:: c

    int _iotx_cm_yield(int fd, unsigned int timeout)
    {
        POINTER_SANITY_CHECK(fd_lock, NULL_VALUE_ERROR);
        iotx_cm_yield_fp yield_func;

        if (fd == -1) {
            int i;
            //CM_MAX_FD_NUM==3
            for (i = 0; i < CM_MAX_FD_NUM; i++) { 
                yield_func = NULL;
                HAL_MutexLock(fd_lock);
                if (_cm_fd[i] != NULL) {
                    yield_func =  _cm_fd[i]->yield_func;  //mqtt连接为_mqtt_yield， coap链接为_coap_yield
                }
                HAL_MutexUnlock(fd_lock);
                if (yield_func != NULL) {
                    yield_func(timeout);
                }
            }
            return 0;
        }

        if (_fd_is_valid(fd) < 0) {
            CM_ERR(ERR_INVALID_PARAMS);
            return -1;
        }

        HAL_MutexLock(fd_lock);
        yield_func =  _cm_fd[fd]->yield_func;
        HAL_MutexUnlock(fd_lock);
        return yield_func(timeout);     //执行
    }