.. _tcp_read:

tcp_read 传输层数据读取
-------------------------------

.. code-block:: c

    //select最大阻塞timeout_ms， 直到读取所有数据
    int32_t HAL_TCP_Read(uintptr_t fd, char *buf, uint32_t len, uint32_t timeout_ms)
    {
        int ret, err_code;
        uint32_t len_recv;
        uint64_t t_end, t_left;
        fd_set sets;
        struct timeval timeout;

        t_end = _linux_get_time_ms() + timeout_ms;
        len_recv = 0;
        err_code = 0;

        do {
            t_left = _linux_time_left(t_end, _linux_get_time_ms()); //计算超时时间
            if (0 == t_left) {
                break;
            }
            FD_ZERO(&sets);
            FD_SET(fd, &sets);

            timeout.tv_sec = t_left / 1000;
            timeout.tv_usec = (t_left % 1000) * 1000;

            ret = select(fd + 1, &sets, NULL, NULL, &timeout); //阻塞在这里，poll状态
            if (ret > 0) {
                ret = recv(fd, buf + len_recv, len - len_recv, 0); //接收数据
                if (ret > 0) {
                    len_recv += ret;
                } else if (0 == ret) {
                    hal_err("connection is closed");
                    err_code = -1;
                    break;
                } else {
                    if (EINTR == errno) {
                        hal_err("EINTR be caught");
                        continue;
                    }
                    hal_err("recv fail");
                    err_code = -2;
                    break;
                }
            } else if (0 == ret) {
                break;
            } else {
                hal_err("select-recv fail");
                err_code = -2;
                break;
            }
        } while ((len_recv < len));

        /* priority to return data bytes if any data be received from TCP connection. */
        /* It will get error code on next calling */
        return (0 != len_recv) ? len_recv : err_code;
    }

