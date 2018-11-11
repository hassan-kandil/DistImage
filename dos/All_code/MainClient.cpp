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
#include <fstream>
#include "base64.h"

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

using namespace std;

int main (){

  Client client;
	std::cout << "Enter Hostname: ";
 	std::string name;
	std::cin >> name;
	char* my_name = new char[name.size() + 1];
	name.copy(my_name, name.size() + 1);
  my_name[name.size()] = '\0';

	int port;
	cout << "Enter the port: ";
	cin >> port;

  // Steganography
	string command, defaultPath,privatePath;
	defaultPath = "default.jpeg";
	privatePath = "rooney.jpeg";
	command = "steghide embed -cf " + defaultPath + " -ef " + privatePath + " -p hk ";

  int nc = command.length();
  char command_char_array[nc+1];

  strcpy(command_char_array, command.c_str());
	int s = system(command_char_array);

  std::ifstream is ("default.jpeg", std::ifstream::binary);

  if (is) {
  	is.seekg (0, is.end); // get length of file
  	unsigned int length = is.tellg();
 	  is.seekg (0, is.beg);
		//cout << "Original Decoded Image Length: "<< length << endl;

   	char * buffer = new  char [length]; // allocate memory
    is.read (buffer,length); // read data as a block
    is.close();
    string x = base64_encode( (const unsigned char *)buffer, length);
    int n = x.length();
    char char_array[n+1];
    strcpy(char_array, x.c_str());
    client.Client::DoOperation(my_name, port, char_array);
  }
  else
    cout << "could'nt open file" << endl;

return 0;
}
