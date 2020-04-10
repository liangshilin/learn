
#include <string>
#include <cerrno>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include "CSocket.h"

using namespace std;

inline int CSocket::Create(bool nonblock)
{
	fd_ = socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == fd_)
	{
		return -1;
	}

	if (nonblock)
	{
		int flags;
		if ((flags = fcntl(fd_, F_GETFL, NULL)) < 0) 
		{
			printf("fcntl(%d, F_GETFL)", fd_);
			return -1;
		}

		if (!(flags & O_NONBLOCK))
		{
			if (fcntl(fd_, F_SETFL, flags | O_NONBLOCK) == -1) 
			{
				printf("fcntl(%d, F_SETFL)", fd_);
				return -1;
			}
		}
	}

	return 0;
}

inline int CSocket::Connect(const string& str_ip, int port)
{
	return Connect(str_ip.c_str(), port);
}

inline int CSocket::Connect(const char* str_ip, int port)
{
	if (strlen(str_ip) == 0 || port <= 0)
	{
		return -1;
	}

	if (fd_ < 0)
	{
		if (-1 == Create())
		{
			printf("create socket error.\n");
			return -1;
		}
	}

	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	const int ret_tmp = inet_pton(AF_INET, str_ip, &addr.sin_addr);

	if (ret_tmp <= 0)
	{
		printf("ip str to ip byte fail.%s, %d\n", __FILE__, __LINE__);
		return ret_tmp;
	}

	if (-1 == connect(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in)))
	{
		printf("connect fail.(%s:%d)\n", str_ip, port);
		return -1;
	}

	return 1;
}

inline int CSocket::Bind(const char* str_ip, int port)
{
	if (fd_ <= 0)
	{
		if (Create() < 0)
		{
			printf("create socket error.\n");
			return -1;
		}	
	}

	socklen_t len_tmp = 0;
	sockaddr_in addr_tmp;
	memset(&addr_tmp, 0, sizeof(sockaddr_in));

	if (-1 == getsockname(fd_, (sockaddr*)&addr_tmp, &len_tmp))
	{
		printf("getsockname fail.\n");
		return -1;
	}

	if (addr_tmp.sin_port > 0)
	{
		printf("bind fail, fd already bind addr.\n");
		return -1;
	}

	auto addr_len = sizeof(sockaddr_in);
	sockaddr_in addr;
	memset(&addr, 0, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, str_ip, &addr.sin_addr);

	if (-1 == bind(fd_, (sockaddr*)& addr, sizeof(sockaddr_in)))
	{
		return -1;
	}

	return 0;
}

inline int CSocket::Bind(string str_ip, int port)
{
	return Bind(str_ip.c_str(), port);
}

inline int CSocket::Listen(int backlog)
{
	if (fd_ <= 0)
	{
		return -1;
	}

	if (backlog <= 0)
	{
		backlog = 16;
	}

	if (-1 == listen(fd_, backlog))
	{
		return -1;
	}
	return 0;
}

inline socket_fd CSocket::Accept()
{
	if (fd_ <= 0)
	{
		return -1;
	}
	sockaddr addr_tmp;
	memset(&addr_tmp, 0, sizeof(sockaddr));
	socklen_t len_tmp = 0;
	return accept(fd_, &addr_tmp, &len_tmp);
}

int CSocket::Read(char* buf, unsigned int buf_size)
{
	if (fd_ <= 0 || buf == nullptr)
	{
		printf("error, fd <= 0 or buf is nullptr\n");
		return -1;
	}

	while (true)
	{
		int recv_size = recv(fd_, buf, buf_size, 0);

		if (recv_size  <= 0)
		{
			if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
			{
				continue;
			}

			printf("recv error(%d): %s", errno, strerror(errno));
			return -1;
		}
		return recv_size;
	}

	return -1;
}

int CSocket::Read(string& buf, int read_size)
{
	unique_ptr<char> buf_tmp(new char[read_size + 1]);
	memset(buf_tmp.get(), 0, read_size + 1);

	int ret_tmp = Read(buf_tmp.get(), read_size);

	if (ret_tmp <= 0)
	{
		return ret_tmp;
	}
	buf.append(buf_tmp.get());

	return ret_tmp;
}

inline int CSocket::GetError(string& errmsg)
{
	perror("error message: ");
	errmsg = strerror(errno);
	return errno;
}
