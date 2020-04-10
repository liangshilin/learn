#pragma once
#ifndef SOCKET_TEST_HPP_
#define SOCKET_TEST_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <cstring>


using namespace std;

class NetSocket
{
public:
	NetSocket();
	~NetSocket();

	static int create_socket()
	{
		int fd = -1;
		if (fd = socket(AF_INET, SOCK_STREAM, 0) < 0)
		{
			//to do
			return -1;
		}

		return fd;
	}

	static int connect_tcp(string ip, int port, int socket_fd = -1)
	{
		int fd = socket_fd;
		if (socket_fd < 0)
		{
			fd = create_socket();
		}

		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		int flag = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

		if (flag < 0)
		{
			// to do
			return -1;
		}

		if (connect(fd, (sockaddr*)&addr, sizeof(sockaddr_in)) < 0)
		{
			// 
			return -1;
		}

		return fd;
	}

	static int listen_tcp(string ip, int port, int socket_fd = -1)
	{
		int fd = socket_fd;
		if (socket_fd < 0)
		{
			fd = create_socket();
		}

		sockaddr_in addr = { 0 };
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		int flag = inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
		
		//¼àÌý±¾µØ
		addr.sin_addr.s_addr = INADDR_ANY;

		if (flag < 0)
		{
			// to do
			return -1;
		}

		if (bind(fd, (sockaddr*)&addr, sizeof(sockaddr_in)) < 0)
		{
			// to do 
			return -1;
		}

		if (listen(fd, 15) < 0)
		{
			//
			return -1;
		}

		return fd;
	}

	static int accept_tcp(int fd, sockaddr* addr = nullptr, unsigned int* addr_len = nullptr)
	{
		return accept(fd, addr, addr_len);
	}

	static int read_tcp(int fd, string& buf, int read_len)
	{
		char buf_tmp[1024] = { 0 };
		buf.clear();

		while (read_len > 0)
		{
			memset(buf_tmp, 0, 1024);
			int size = read(fd, buf_tmp, 1024);

			if (size > 0)
			{
				buf.append(buf_tmp);
				if (size < 1024)
				{
					break;
				}

				read_len -= size;
			}
			else if (size = 0)
			{
				//
				return -1;
			}
			else
			{
				if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
				{
					continue;
				}

				//
				return -1;
			}
		}

		return buf.size();
	}

	static int write_tcp(int fd, string buf)
	{
		int size = 0;
		while (size >= buf.size())
		{
			int w_size = write(fd, buf.c_str() + size, buf.size() - size);
			if (w_size <= 0)
			{
				if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
				{
					continue;
				}

				//
				return -1;
			}
			else
			{
				size += w_size;
			}
		}	

		return size;
	}
	
private:

};

NetSocket::NetSocket()
{
}

NetSocket::~NetSocket()
{
}


#endif // !SOCKET_TEST_HPP_
