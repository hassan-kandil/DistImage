#ifndef MESSAGE_H
#define MESSAGE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <stdio.h>

using namespace std;
enum MessageType { Request, Reply};
class Message
{
	private:
		MessageType message_type;
		void * message;
		size_t message_size;

		public:
		Message(void * p_message, size_t p_message_size);
		//Message(char * marshalled_base64);
		//char * marshal();
		//int getOperation ();
		//int getRPCId();
		void * getMessage();
		size_t getMessageSize();
		MessageType getMessageType();
		//void setOperation (int _operation);
		void setMessage (void * message,size_t message_size);
		void setMessageType (MessageType message_type);
		~Message();



};
#endif 
