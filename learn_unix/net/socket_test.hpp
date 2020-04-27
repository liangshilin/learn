#pragma once
#ifndef SOCKET_TEST_HPP_
#define SOCKET_TEST_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <cstring>
#include <csignal>


using namespace std;
class NetSocket
{
public:
	NetSocket() = default;
	~NetSocket() = default;
	
	static int set_noblock(const int& fd)
	{
		// todo 异常处理待添加
		int state = fcntl(fd, F_GETFL, 0);
		fcntl(fd, F_SETFL, O_NONBLOCK | state);
		return 1;
	}

	static int create_socket()
	{
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < 0)
		{
			//to do
			return -1;
		}

		//set SO_REUSEADDR //服务挂掉可以马上监听同意端口
		// ingnore SIGPIPE //对端异常关闭连接，read会触发SIGPIPE信号
		//set TCP_NODELAY  //不使用发送优化算法，会增加响应时间

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

	static int connect_tcp_nonb(string ip, int port, int nsec, int socket_fd = -1)
	{
		int sockfd = socket_fd;
		if (socket_fd < 0)
		{
			sockfd = create_socket();
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

		int				flags, n, error;
		socklen_t		len;
		fd_set			rset, wset;
		struct timeval	tval;

		flags = fcntl(sockfd, F_GETFL, 0);
		fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

		error = 0;
		if ((n = connect(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0))
			if (errno != EINPROGRESS)
				return(-1);

		/* Do whatever we want while the connect is taking place. */

		if (n == 0)
			goto done;	/* connect completed immediately */

		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);
		wset = rset;
		tval.tv_sec = nsec;
		tval.tv_usec = 0;

		if ((n = select(sockfd + 1, &rset, &wset, NULL, nsec ? &tval : NULL)) == 0) {
			close(sockfd);		/* timeout */
			errno = ETIMEDOUT;
			return(-1);
		}

		if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
			len = sizeof(error);
			if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
				return(-1);			/* Solaris pending error */
		}
		else
			fprintf(stderr, "select error: sockfd not set");

	done:
		fcntl(sockfd, F_SETFL, flags);	/* restore file status flags */

		if (error) {
			close(sockfd);		/* just in case */
			errno = error;
			return(-1);
		}
		return(0);
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
		
		//监听本地
		//addr.sin_addr.s_addr = INADDR_ANY;

		if (flag < 0)
		{
			// to do
			return -1;
		}

		int optval = 1;
		// 重用地址
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
		// 禁止Nagle算法
		optval = 0;
		setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
		// ingnore SIGPIPE
		signal(SIGPIPE, SIG_IGN);


		if (bind(fd, (sockaddr*)&addr, sizeof(sockaddr_in)) < 0)
		{
			cout << strerror(errno) << endl;
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

// example
namespace NetSocket_ {
void run1(bool first_close)
{
	int fd = NetSocket::listen_tcp("0.0.0.0", 44444);
	vector<int> sockets;
	while (true)
	{
		fprintf(stdout, "waiting connect...\n");
		int client_fd = NetSocket::accept_tcp(fd);

		string tmp;
		NetSocket::read_tcp(client_fd, tmp, 1024);
		fprintf(stdout, "read[%d]: %s\n", client_fd, tmp.c_str());
		NetSocket::write_tcp(client_fd, "OK");
		fprintf(stdout, "write[%d]: OK\n", client_fd);

		if (first_close)
		{
			shutdown(client_fd, SHUT_WR);
		}
		else
		{
			sockets.push_back(client_fd);
		}
	}

}
}

#endif // !SOCKET_TEST_HPP_
