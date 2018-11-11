
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
using namespace std;
#define BUFFER_SIZE 3000000
#define LITTLE_BUFFER_SIZE 20000
#include "base64.h"

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const &encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && (encoded_string[in_] != '=') &&
         is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_];
    in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] =
          (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] =
          ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = 0; j < i; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] =
        ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

    for (j = 0; (j < i - 1); j++)
      ret += char_array_3[j];
  }

  return ret;
}

bool con = true;
Server::Server(int port) { sv = new UDPSocketServer(port); }

void Server::getRequest() {
  printf("%s.\n", "Start of getRequest");
  unsigned long current_received = 0;
  memset(buffer, 0, sizeof(buffer));
  std::ofstream os("new_2.jpeg");
  memset(little_buffer, 0, sizeof(little_buffer));
  // Receive Image Length
  r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
               (struct sockaddr *)&recievedAddr, &addresslength);
  printf("Received Length of Encoded Message (char[]) = %s.\n", little_buffer);
  // Change to unsigned long
  unsigned long received_length = 0;
  for (int i = 0; i < LITTLE_BUFFER_SIZE && little_buffer[i] != '\0'; i++) {
    received_length *= 10;
    received_length += little_buffer[i] - '0';
  }

  // Reply with Length
  memset(little_buffer, 0, sizeof(little_buffer));
  sprintf((char *)(little_buffer), "%lu", received_length);
  if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
             (struct sockaddr *)&recievedAddr, addresslength) < 0) {
    perror("length reply sendto failed");
  }

  printf("Received Length of Encoded Message (lu) = %lu.\n", received_length);

  // Start Receiving Image
  while (current_received < received_length) {
    printf("%s\n", "Loop Start:");
    memset(little_buffer, 0, sizeof(little_buffer));

    r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                 (struct sockaddr *)&recievedAddr, &addresslength);

    current_received += r;
    printf("Received total %lu encoded bytes.\n", current_received);
    std::string sName(reinterpret_cast<char *>(little_buffer));
    string y = base64_decode(sName);

    if (r > 0)
      os << y;
    memset(little_buffer, 0, sizeof(little_buffer));
    sprintf((char *)(little_buffer), "%lu", current_received);

    if (sendto(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
               (struct sockaddr *)&recievedAddr, addresslength) < 0) {
      perror("sendto failed");
    }
  }
  os.close();

  // Steganography
  string extract_command, defaultPath = "default.jpeg";
  extract_command = "steghide extract -sf " + defaultPath + " -p hk";
  int n = extract_command.length();
  char char_array[n + 1];

  strcpy(char_array, extract_command.c_str());
  system(char_array);
}

void Server::sendReply() {
  if (sendto(sv->s, buffer, r, 0, (struct sockaddr *)&recievedAddr,
             addresslength) < 0) {
    perror("sendto failed");
  }
}

bool Server::serveRequests() { getRequest(); }

Server::~Server() {}
