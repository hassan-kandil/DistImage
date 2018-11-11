#ifndef UDPSOCKETSERVER_H
#define UDPSOCKETSERVER_H
class UDPSocketServer
{
	
	public:
		int s;
		UDPSocketServer(int port);
		bool initializeServer (int port);
		~UDPSocketServer ( );	
};
#endif 
