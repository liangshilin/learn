#pragma once
#ifndef NET_UDP_TEST_HPP_
#define NET_UDP_TEST_HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <cstring>

#define SERV_PORT 22222

using namespace std;
class NetUdp
{
public:
	NetUdp();
	virtual ~NetUdp();

	void server1()
	{
		int					sockfd;
		struct sockaddr_in	servaddr, cliaddr;

		sockfd = socket(AF_INET, SOCK_DGRAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(SERV_PORT);

		bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));

		char mesg[512];
		int count = 0;

		for (; ; ) {
			socklen_t len = sizeof(cliaddr);
			auto size = recvfrom(sockfd, mesg, 512, 0, (sockaddr*)&cliaddr, &len);

			fprintf(stdout, "from client:[%d] %s\n", size, mesg);
			count++;
		}
	}

private:

};

NetUdp::NetUdp()
{

}

NetUdp::~NetUdp()
{

}





#endif // !NET_UDP_TEST_HPP_
