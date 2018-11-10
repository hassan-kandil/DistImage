#include "Peer.h"

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

using namespace std;

int main() {
  Peer peer;
  cout << peer.sign_up("Refoss", "hamada100") << endl;
  return 0;
}

/*
// Steganography
string command, defaultPath, privatePath;
defaultPath = "default.jpeg";
privatePath = "rooney.jpeg";
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
  // cout << "Original Decoded Image Length: "<< length << endl;

  char *buffer = new char[length]; // allocate memory
  is.read(buffer, length);         // read data as a block
  is.close();
  string x = base64_encode((const unsigned char *)buffer, length);
  int n = x.length();
  char char_array[n + 1];
  strcpy(char_array, x.c_str());
  peer.Peer::DoOperation(dos_ip, dos_port, char_array);
} else
  cout << "could'nt open file" << endl;
  */
