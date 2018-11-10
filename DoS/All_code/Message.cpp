#include "Message.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>





Message:: Message(void * p_message, size_t p_message_size){
	this.message= p_message; 
	this.message_size= p_message_size;
}

void * Message:: getMessage(){
	return message;

}

size_t Message::getMessageSize(){
	return message_size;
}

MessageType Message::getMessageType(){
	return message_type;
}

void Message::setMessage (void * message,size_t message_size){
	this.message= message; 
	this.message_size= message_size;
}
void Message::setMessageType (MessageType message_type){
	this.message_type= message_type;
}
Message::~Message(){}
