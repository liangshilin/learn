#pragma once
#ifndef POLL_TEST_H_
#define POLL_TEST_H_

#include <vector>
#include <string>
#include <iostream>
#include <sys/select.h>
#include "socket_test.hpp"

using namespace std;

class NetSelect
{
public:
	NetSelect() = default;
	~NetSelect() = default;

	void select_test()
	{
		int listen_fd = NetSocket::listen_tcp("", 22222, -1);

		vector<int> fd_array(1000);
		fd_set read_set, write_set;
		int max_fd = listen_fd;
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;

		fd_array.push_back(listen_fd);
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_SET(listen_fd, &read_set);

		while (true)
		{
			int flag = select(max_fd + 1, &read_set, &write_set, nullptr, &timeout);

			if (flag > 0)
			{
				for (auto fd_tmp : fd_array)
				{
					if (FD_ISSET(fd_tmp, &read_set))
					{
						//处理服务新连接
						if (fd_tmp == listen_fd)
						{
							int client_fd = accept(listen_fd, nullptr, nullptr);
							if (client_fd < 0)
							{
								if (errno == EINTR)
								{
									continue;
								}

								//
								break;
							}
							else
							{
								FD_SET(client_fd, &read_set);
								fd_array.push_back(client_fd);
							}
						}
						else
						{
							string buf_tmp;
							int r_size = 0;
							if (r_size = NetSocket::read_tcp(fd_tmp, buf_tmp, 2048) < 0)
							{
								//
								FD_CLR(fd_tmp, &read_set);

								close(fd_tmp);
								//补充删除fd_tmp
								continue;
							}
							
							if (r_size < 2048)
							{
								FD_CLR(fd_tmp, &read_set);
								FD_SET(fd_tmp, &write_set);
							}
												
							cout << "read: " << buf_tmp << endl;
						}
					}

					if (FD_ISSET(fd_tmp, &write_set))
					{
						string buf_tmp(1025, 'A');
						if (NetSocket::write_tcp(fd_tmp, buf_tmp) < 0)
						{
							//
							FD_CLR(fd_tmp, &write_set);
							close(fd_tmp);
							//补充删除fd_tmp
							continue;
						}
						else
						{
							cout << "write: " << buf_tmp << endl;
							FD_CLR(fd_tmp, &write_set);
							FD_SET(fd_tmp, &read_set);
						}
					}
				}
			}
		}


	}

private:
};


#endif // !POOL_TEST_H_

