Client: g++ Client.h UDPSocketClient.cpp mainClient.cpp -o client
Server: g++ Server.cpp UDPSocketServer.cpp MainServer.cpp -o server

DoS: g++ DoS.h UDPSocketServer.h MainDoS.cpp -o dos
Peer: g++ Peer.h UDPSocketClient.h MainPeer.cpp -o peer
