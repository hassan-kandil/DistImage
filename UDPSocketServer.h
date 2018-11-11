#ifndef UDPSOCKETSERVER_H
#define UDPSOCKETSERVER_H
#include "UDPSocketServer.h"
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

class UDPSocketServer {

public:
  int s;
  UDPSocketServer(int port) { initializeServer(port); }
  bool initializeServer(int port) {

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("cannot create socket");
      return 0;
    }

    struct sockaddr_in serverAddr;

    memset((char *)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(s, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
      perror("bind failed");
      return 0;
    }
  }

  ~UDPSocketServer() {}
};
#endif
