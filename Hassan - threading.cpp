#include "Client.h"
#include "base64.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
using namespace std;
static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const *bytes_to_encode,
                          unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] =
          ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] =
          ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] =
        ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] =
        ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while ((i++ < 3))
      ret += '=';
  }

  return ret;
}

static void sendImage(Client *client, string privatePath, string name,
                      int port) {

  string command, defaultPath;
  char *my_name = new char[name.size() + 1];
  name.copy(my_name, name.size() + 1);
  my_name[name.size()] = '\0';
  defaultPath = "default.jpeg";
  command =
      "steghide embed -cf " + defaultPath + " -ef " + privatePath + " -p hk ";

  int nc = command.length();
  char command_char_array[nc + 1];

  strcpy(command_char_array, command.c_str());
  int s = system(command_char_array);

  std::ifstream is("default.jpeg", std::ifstream::binary);

  if (is) {
    is.seekg(0, is.end); // get length of file
    unsigned int length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char[length]; // allocate memory
    is.read(buffer, length);         // read data as a block
    is.close();
    string x = base64_encode((const unsigned char *)buffer, length);
    int n = x.length();
    char char_array[n + 1];
    strcpy(char_array, x.c_str());
    client->DoOperation(my_name, port, char_array);
  } else
    cout << "could'nt open file" << endl;
}

int mainClient(string hostname, int port, string privatePath,
               bool grantRequest) {

  std::string name;
  std::string privatePath;
  int port;
  Client *client = new Client;
  bool grantRequest = true;

  while (true) {
    /*std::cout << "Enter Hostname: ";
    std::cin >> name;

    cout <<"Enter Image Name: ";
    cin >> privatePath;



    cout << "Enter the port: ";
    cin >> port;

    */

    if (grantRequest) {
      thread t1(sendImage, client, move(privatePath), move(name), move(port));
      t1.detach();
    }
  }

  return 0;
}
