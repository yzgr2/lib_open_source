.. _conn_yield_setup:

连接 handle 设置
------------------------

全局变量中的_cm_fd[i]->yield_func，在如下流程中设置：

``iotx_cm_open`` 根据用户传入的参数，保存连接参数, 并初始化handle

.. code-block:: c

    int iotx_cm_open(iotx_cm_init_param_t *params)
    {
        int fd;
        iotx_cm_connection_t *connection = NULL;

        switch (params->protocol_type) {
            case IOTX_CM_PROTOCOL_TYPE_MQTT:
                connection = iotx_cm_open_mqtt(params); //初始化mqtt连接
                break;
            case IOTX_CM_PROTOCOL_TYPE_COAP:
                connection = iotx_cm_open_coap(params); //初始化coap连接
                break;            
            default:
                CM_WARN("protocol %d not support yet", params->protocol_type);
                break;
        }

        fd = _get_fd(connection);   //设置到全局变量_cm_fd[]中
        if (fd < 0) {
            CM_ERR("get fd failed");
            connection->close_func();
            return -1;
        }
        connection->fd = fd;    
    }

    static int _get_fd(iotx_cm_connection_t *handle)
    {
        int i;
        POINTER_SANITY_CHECK(handle, NULL_VALUE_ERROR);

        //...加锁 fd_lock    
        for (i = 0; i < CM_MAX_FD_NUM; i++) {
            if (_cm_fd[i] == NULL) {
                _cm_fd[i] = handle;     // 设置handle
                HAL_MutexUnlock(fd_lock);
                return i;
            }
        }    
        //...释放锁
        return -1;
    }

``iotx_cm_open_mqtt`` 具体保持连接参数，并初始化handle

.. code-block:: c

    iotx_cm_connection_t *iotx_cm_open_mqtt(iotx_cm_init_param_t *params)
    {
        _set_common_handlers(); //mqtt定义的static函数
    }

    static void _set_common_handlers()
    {
        if (_mqtt_conncection != NULL) {
            _mqtt_conncection->connect_func = _mqtt_connect;
            _mqtt_conncection->sub_func = _mqtt_sub;
            _mqtt_conncection->unsub_func = _mqtt_unsub;
            _mqtt_conncection->pub_func = _mqtt_publish;
            _mqtt_conncection->yield_func = (iotx_cm_yield_fp)_mqtt_yield; //轮询用
            _mqtt_conncection->close_func = _mqtt_close;
        }
    }

