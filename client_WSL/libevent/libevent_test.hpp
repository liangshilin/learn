#pragma once
#ifndef LIBEVENT_TEST_HPP_
#define LIBEVENT_TEST_HPP_

#include<netinet/in.h>  
#include<sys/socket.h>  
#include<unistd.h>  
#include<stdio.h>  
#include<string.h>  
#include<event2/listener.h>  
#include<event2/bufferevent.h>  
#include<event2/thread.h>
#include <event.h>

#include <string>
#include "blocking_q.h"

class LibeventTest
{
public:
	LibeventTest() :base_(nullptr) {}
	~LibeventTest()
	{
		event_base_free(base_);
	}

	void test()
	{
		if (base_ != nullptr)
			event_base_free(base_);
		base_ = event_base_new();

        //evthread_use_pthreads();//enable threads  

        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(struct sockaddr_in));
        sin.sin_family = AF_INET;
        sin.sin_port = htons(44444);

        evconnlistener* listener = evconnlistener_new_bind(base_, listener_cb, base_,
                LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE| LEV_OPT_REUSEABLE_PORT,
                10, (struct sockaddr*) & sin,
                sizeof(struct sockaddr_in));

        event_base_dispatch(base_);

        evconnlistener_free(listener);
        event_base_free(base_);

        return ;

	}

private:
    static void listener_cb(evconnlistener* listener, evutil_socket_t fd,
        struct sockaddr* sock, int socklen, void* arg)
    {
        auto client_sa = (sockaddr_in*)sock;
        auto addr_ip = inet_ntoa(client_sa->sin_addr);
        auto addr_port = ntohs(client_sa->sin_port);
        printf("accept a client[%s:%d] %d\n", addr_ip, addr_port, fd);

        event_base* base = (event_base*)arg;

        //为这个客户端分配一个bufferevent  
        bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE| BEV_OPT_THREADSAFE);

        bufferevent_setcb(bev, socket_read_cb, NULL, socket_event_cb, NULL);
        bufferevent_enable(bev, EV_READ | EV_PERSIST);
    }


    static void socket_read_cb(bufferevent* bev, void* arg)
    {
        char msg[1024];
        size_t len = bufferevent_read(bev, msg, sizeof(msg) - 1);
        msg[len] = '\0';
        printf("server read the data %s\n", msg);

        //解包
        buf_.append(msg);
        if (buf_.length() > 8)
        {
            auto pbuf = buf_.substr(0, 8);
            int size = strtol(pbuf.c_str(), nullptr, 10);
            if (buf_.length() >= size)
            {
                if (!requests_.enqueue_noblock(buf_.substr(0, size)))
                {           
                    char reply[] = "system busy! please try again.";
                    bufferevent_write(bev, reply, strlen(reply));
                }
                buf_.erase(0, size);
            }
        }
    }


    static void socket_event_cb(bufferevent* bev, short events, void* arg)
    {
        if (events & BEV_EVENT_EOF)
            printf("connection closed\n");
        else if (events & BEV_EVENT_ERROR)
            printf("some other error\n");

        //这将自动close套接字和free读写缓冲区  
        bufferevent_free(bev);
    }

private:
    static string buf_;
	event_base* base_;
    static mpmc_blocking_queue<string> requests_;
};

string LibeventTest::buf_;
mpmc_blocking_queue<string> LibeventTest::requests_(200);

#endif // !LIBEVENT_TEST_HPP_
