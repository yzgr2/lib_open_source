.. _diagram:


流程图
--------------------

应用层主流程
````````````````````

.. uml:: 
   
   @startuml
   start

    while (1?)
    :IOT_Linkkit_Yield(200ms);
    :user_function();    
    endwhile

   stop
   @enduml


IOT_Linkkit_Yield
````````````````````

.. uml:: 
   
   @startuml
   start

    repeat 
        :connection layer's yield_func(200ms)\nmqtt_yeild(200ms) or coap_yield(200ms);      
    repeat while (more connection layer ?)

    :iotx_dm_dispatch();

   stop
   @enduml


IOT_MQTT_Yield
````````````````````

.. uml:: 
   
   @startuml
   start

    repeat 
        :keepalive检查，重连;
        :带超时阻塞收包，处理mqtt报文 ;    
    repeat while (时间未用完 ?)   

   stop
   @enduml


iotx_dm_dispatch
````````````````````

.. uml:: 
   
   @startuml
   start

    repeat 
        :ctx->msg_list.message_list列表取出第一个消息;
        :ctx->event_callback(msg->type, msg->data)处理消息;
        :count++;       
    repeat while (count < 50 ?)   

   stop
   @enduml
