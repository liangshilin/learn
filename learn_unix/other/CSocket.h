#pragma once
#ifndef CSOCKET_H_
#define CSOCKET_H_

#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;
using socket_fd = int;

class CSocket
{
public:
	CSocket() :fd_(-1) {}

	virtual ~CSocket()
	{
		if (fd_ >= 0)
		{
			close(fd_);
		}
	}

public:
	inline int Create(bool nonblock = true);

	//return 1 sucess,other fail
	inline int Connect(const string& str_ip, int port);

	//return 1 sucess,other fail
	inline int Connect(const char* str_ip, int port);

	inline int Bind(const char* str_ip, int port);

	inline int Bind(string str_ip, int port);

	inline int Listen(int backlog);

	inline socket_fd Accept();

	//return 0(socket close), -1(error)
	int Read(char* buf, unsigned int buf_size);

	int Read(string& buf, int read_size);

	inline int GetError(string& err_msg);

private:
	socket_fd fd_;
};


#endif // !CSOCKET_H_
