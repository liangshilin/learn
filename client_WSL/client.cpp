
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "other/virtual_test.hpp"
#include "stl/map_test.hpp"
#include "protobuf/protobuf_test.hpp"
#include "libevent/libevent_test.hpp"

#define SERV_PORT 22222

using namespace std;

int main(int argc, char* argv[])
{
	

	LibeventTest test;
	test.test();
	exit(0);

	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		fprintf(stderr, "usage: udpcli <IPaddress>");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "129.28.195.156", &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	int		i, n;
	char	sendline[512];
	memset(sendline, 'A', 511);
	sendline[512] = 0;

	n = 100 * 1024;
	//Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &n, sizeof(n));
	while (true)
	{
		//gets(sendline);
		usleep(1000);
		auto size = sendto(sockfd, sendline, 512, 0, (sockaddr*)&servaddr, sizeof(servaddr));
		fprintf(stdout, "send server:[%d] %s\n", size, sendline);
	}

    fprintf(stdout, "hello client!\n");
}


