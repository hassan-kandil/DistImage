Client: g++ Client.h UDPSocketClient.cpp mainClient.cpp -o client
Server: g++ Server.cpp UDPSocketServer.cpp MainServer.cpp -o server

DoS: g++ DoS.h UDPSocketServer.h MainDoS.cpp Message.h -o dos
Peer: g++ Peer.h UDPSocketClient.h MainPeer.cpp -o peer


Git:
git status
git add -u
git commit -m ""
git push origin master
git pull origin master
git ls-tree -r master --name-only // know tracked files
git reset -- dos/users.txt // if want users to be untracked
