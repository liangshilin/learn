#pragma once
#ifndef NET_EPOLL_TEST_HPP_
#define NET_EPOLL_TEST_HPP_

#include <string>
#include <list>
#include <stack>
#include <memory>
#include <iostream>
#include <sys/epoll.h>
#include <unordered_map>
#include <boost/format.hpp>
#include "socket_test.hpp"

using namespace std;
//using namespace boost;
 
#define STRING_POOL_NUM 10

class StringPool
{
	using element = unique_ptr<string>;
private:
	StringPool() 
	{
		for (int i = 0; i < STRING_POOL_NUM; i++)
		{
			poll_.push(make_unique<string>());
		}
	}

	~StringPool() = default;

public:
	static StringPool* getInstance()
	{
		static StringPool __string_pool;
		return &__string_pool;
	}

	//拉取string缓冲区
	element&& poll()
	{
		if (poll_.empty)
		{
			return make_unique<string>();
		}

		auto ptr = move(poll_.top());
		poll_.pop();
		return move(ptr);
	}

	// 推入string缓冲区
	void push(element&& ptr)
	{
		poll_.push(move(ptr));
	}

private:
	stack<unique_ptr<string>> poll_;
};


class ServerConnect
{
public:
	ServerConnect(int fd, unique_ptr<string>&& buf) :fd_(fd), buf_(move(buf)) {}
	~ServerConnect()
	{
		StringPool::getInstance()->push(move(buf_));
	}

public:
	int fd_;
	unique_ptr<string> buf_;
	
};

class NetEpoll
{
public:
	NetEpoll() :loop_flag(true) {};
	~NetEpoll()
	{
		close(epoll_fd_);
	}

	void test()
	{
		epoll_fd_ = epoll_create(1024);
		if (epoll_fd_ < 0)
		{
			cout << boost::format("epoll_create fail[%s]") % strerror(errno) << endl;
			return;
		}

		epoll_event ep_event;
		memset(&ep_event, 0, sizeof(ep_event));

		int listen_fd = NetSocket::listen_tcp("0.0.0.0", 44444);
		ep_event.data.fd = listen_fd;
		ep_event.events = EPOLLIN;

		// 设置socket非阻塞
		int state = fcntl(listen_fd, F_GETFL, 0);
		fcntl(listen_fd, F_SETFL, O_NONBLOCK | state);

		if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_fd, &ep_event) < 0)
		{
			cout << boost::format("epoll_create fail[%s]") % strerror(errno) << endl;
			return;
		}

		int count = 0;
		unique_ptr<epoll_event[]> events(make_unique<epoll_event[]>(1024));
		while (loop_flag)
		{
			count = epoll_wait(epoll_fd_, events.get(), 1024, 100);
			if (0 == count || errno == EINTR)
			{
				continue;
			}
			else if(count < 0)
			{
				cout << boost::format("epoll_create fail[%s]") % strerror(errno) << endl;
				return;
			}

			//事件处理
			for (int i = 0; i < count; i++)
			{
				// 新连接
				if (events[i].data.fd == listen_fd)
				{
					accept_operate(listen_fd);
				}

				if (events[i].events & EPOLLIN)
				{

				}

				if(events[i].events & EPOLLOUT)
				{

				}

			}
		}

	}
private:
	void set_noblock(const int& fd)
	{
		int state = fcntl(fd, F_GETFL, 0);
		fcntl(fd, F_SETFL, O_NONBLOCK | state);
	}

	void accept_operate(int listen_fd)
	{
		for (int i = 0; i < 15; i++)
		{
			int client_fd = NetSocket::accept_tcp(listen_fd);

			if (client_fd < 0)
			{
				if (errno == EAGAIN)
				{
					return;
				}
				else
				{
					cout << boost::format("epoll_create fail[%s]") % strerror(errno) << endl;
					exit(errno);
				}
			}

			set_noblock(client_fd);
			auto conn = new ServerConnect(client_fd, StringPool::getInstance()->poll());
			server_conns[client_fd] = conn;

			epoll_event ev_tmp;
			ev_tmp.data.fd = client_fd;
			ev_tmp.data.ptr = conn;
			ev_tmp.events = EPOLLIN;

			if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, client_fd, &ev_tmp) < 0)
			{
				cout << boost::format("epoll_ctl fail[%s]") % strerror(errno) << endl;
				exit(errno);
			}
		}
	}

	void read_operate(int fd, void* ptr)
	{
		auto server_conn = (ServerConnect*)ptr;

		if (NetSocket::read_tcp(fd, *server_conn->buf_, 2048) < 0)
		{
			epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr);
			close(fd);
			delete ptr;
			//delete server_conns[fd];
			server_conns.erase(fd);
		}
		
	}

private:
	int epoll_fd_;
	bool loop_flag;
	unordered_map<int, ServerConnect*> server_conns;
};

#endif // !NET_EPOLL_TEST_HPP_
