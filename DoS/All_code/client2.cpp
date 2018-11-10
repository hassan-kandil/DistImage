#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Client.h"
#include <iostream>
using namespace std;
int main (){
	Client client;
	std::cout<<"Enter Hostname: ";
 	std::string name;
	std::cin>>name;
	char *my_name = new char[name.size() + 1];
	name.copy(my_name, name.size() + 1);
    	my_name[name.size()] = '\0';
	int port;
	cout <<"Enter the port: ";
	cin >> port;
	while(1){
	string s = "lotfy";
	char *my_message = new char[s.size() + 1];
	s.copy(my_message, s.size() + 1);
    	my_message[s.size()] = '\0';
	
	if(my_message != "")
		client.Client::DoOperation(my_name, 8000, my_message);


	string s1 = "ahmed";
	char *my_message1 = new char[s1.size() + 1];
	s1.copy(my_message1, s1.size() + 1);
    	my_message1[s1.size()] = '\0';
	
	if(my_message1 != "")
		client.Client::DoOperation(my_name, 8000, my_message1);

	string s2 = "hassan";
	char *my_message2 = new char[s2.size() + 1];
	s2.copy(my_message2, s2.size() + 1);
    	my_message2[s2.size()] = '\0';
	
	if(my_message2 != "")
		client.Client::DoOperation(my_name, port, my_message2);

	}


return 0;
}
