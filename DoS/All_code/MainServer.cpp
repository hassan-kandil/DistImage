
#include<string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Server.h"
#include <iostream>

using namespace std;

int main (){
	int port;
	cout <<"Enter the port: ";
	cin >> port;
	Server server(port);
	while((server.serveRequests()))
		{
		}


return 0;
}
