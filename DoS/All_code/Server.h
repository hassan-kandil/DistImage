#ifndef SERVER_H
#define SERVER_H
#define BUFFER_SIZE 3000000
#define LITTLE_BUFFER_SIZE 20000

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "UDPSocketServer.h"

class Server
{
	private:
		UDPSocketServer * sv;
	public:
		int r;

		struct sockaddr_in recievedAddr;

 		socklen_t addresslength = sizeof(recievedAddr);

		unsigned char buffer[BUFFER_SIZE];
		unsigned char little_buffer[LITTLE_BUFFER_SIZE];

		Server(int port);
		void getRequest();
		void sendReply();
		bool serveRequests();
		~Server();
};
#endif
