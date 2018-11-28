#include "UDPSocketClient.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//# define SIZE 8
#define BUFFER_SIZE 20000

#ifndef CLIENT_H
#define CLIENT_H
using namespace std;

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

class Client {
private:
  UDPSocketClient *sc;
  int s, n;
  unsigned char *buffer[BUFFER_SIZE];

public:
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

  Client() { sc = new UDPSocketClient(); }
  ~Client() {}
  bool DoOperation(char *machine, int port, char message[]) {
    printf("%s.\n", "Start of DoOperation");
    struct sockaddr_in yourSocketAddress, peerSocketAddress;
    socklen_t peerAddrlen;
    makeDestSA(&yourSocketAddress, machine, port);

    char char_array[10001];

    int current_length = 0;
    int r = 1;
    unsigned char little_buffer[10];
    memset(little_buffer, 0, sizeof(little_buffer));

    printf("Length of Encoded Message = %lu.\n", strlen(message));

    // Send Image Length
    unsigned long received_length = 0;

    while (received_length != strlen(message)) { // != strlen(message)
      received_length = 0;
      sprintf((char *)little_buffer, "%lu", strlen(message));

      if ((n = sendto(sc->s, little_buffer, strlen((const char *)little_buffer),
                      0, (struct sockaddr *)&yourSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                        (struct sockaddr *)&peerSocketAddress, &peerAddrlen)) <
          0)
        perror("Receive Failed");

      // Change to unsigned long
      for (int i = 0; i < 10 && little_buffer[i] != '\0'; i++) {
        received_length *= 10;
        received_length += little_buffer[i] - '0';
      }
    }

    printf("Received Length of Encoded Message = %s.\n", little_buffer);
    unsigned long fakka = strlen(message) % 10000; // last image chunk

    // Start Sending Image
    while (current_length <
           strlen(message)) { //  && r == 1 && little_buffer[0] == '1'
      printf("%s\n", "Loop Start:");
      if (current_length + 10000 < strlen(message)) {
        memcpy(char_array, message + (current_length), 10000);
        current_length += 10000;
        char_array[10000] = 0;
      } else {
        memcpy(char_array, message + (current_length), fakka);
        current_length += fakka;
        char_array[fakka] = 0; // C-String terminate
      }
      if ((n = sendto(sc->s, char_array, strlen(char_array), 0,
                      (struct sockaddr *)&yourSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");
      printf("Current Sent Total = %d.\n", current_length);

      memset(little_buffer, 0, sizeof(little_buffer));
      if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                        (struct sockaddr *)&peerSocketAddress, &peerAddrlen)) <
          0)
        perror("Receive Failed");
      // Change to unsigned long
      received_length = 0;
      for (int i = 0; i < 10 && little_buffer[i] != '\0'; i++) {
        received_length *= 10;
        received_length += little_buffer[i] - '0';
      }

      if (received_length != current_length) {
        perror("Dropped packets! received_length != current_length.");
        current_length = received_length; // Drop Tolerance
      }

      printf("Current Received Total %d.\n", current_length);
    }
    printf("%s", "Message Sent. ");
    printf("Current %d.\n", current_length);
  }

  void makeDestSA(struct sockaddr_in *sa, char *hostname, int port) {
    struct hostent *host;
    sa->sin_family = AF_INET;
    if ((host = gethostbyname(hostname)) == NULL) {
      printf("Unknown host name\n");
      exit(-1);
    }
    sa->sin_addr = *(struct in_addr *)(host->h_addr);
    sa->sin_port = htons(port);
  }
};

#endif
