.. _dispatch:

事件处理
-------------

.. code-block:: c

    void iotx_dm_dispatch(void)
    {
        int count = 0;
        void *data = NULL;
        dm_api_ctx_t *ctx = _dm_api_get_ctx();

    #if !defined(DM_MESSAGE_CACHE_DISABLED)
        dm_msg_cache_tick(); //检查dmc_list列表中的时间戳，如果超时，
                            //构造一个消息并dm_msg_send_to_user
    #endif
    #if defined(OTA_ENABLED) && !defined(BUILD_AOS)
        dm_cota_status_check();
        dm_fota_status_check();
    #endif
        while (CONFIG_DISPATCH_QUEUE_MAXLEN == 0 || count++ < CONFIG_DISPATCH_QUEUE_MAXLEN) {
            if (dm_ipc_msg_next(&data) == SUCCESS_RETURN) 
            {
                //ctx->msg_list.message_list列表头取出一个消息
                dm_ipc_msg_t *msg = (dm_ipc_msg_t *)data;

                //callback 函数为_iotx_linkkit_event_callback(iotx_dm_event_types_t type, char *payload)
                if (ctx->event_callback) {
                    ctx->event_callback(msg->type, msg->data);
                }

                if (msg->data) {
                    DM_free(msg->data);
                }
                DM_free(msg);
                data = NULL;
            } else {
                break;
            }
        }
    }

    static void _iotx_linkkit_event_callback(iotx_dm_event_types_t type, char *payload)
    {
        //1. payload 为json格式， 解析json，获取各回调需要的参数
        //2.根据type执行 用户和sdk注册回调
        switch (type) {
            case IOTX_DM_EVENT_CLOUD_CONNECTED: {
                //g_impl_event_map[evt].callback
                callback = iotx_event_callback(ITE_CONNECT_SUCC);
                if (callback) {
                    ((int (*)(void))callback)();
                }
            }
            case xxx :
            //....
        }
    }

