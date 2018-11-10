#include "UDPSocketClient.h"
#include "base64.h"
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

#include <fstream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define BUFFER_SIZE 50000

#ifndef PEER_H
#define PEER_H
#define LITTLE_BUFFER_SIZE 50000
using namespace std;

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";
/*
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}
*/

class Peer {
private:
public:
  char *dos_ip;
  int dos_port;
  UDPSocketClient *sc;
  int s, n;
  unsigned char *buffer[BUFFER_SIZE];
  Peer() {}
  ~Peer() {}

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

  bool sendImage(char *machine, int port, char message[]) {
    printf("%s.\n", "Start of DoOperation");
    struct sockaddr_in yourSocketAddress, peerSocketAddress;
    socklen_t peerAddrlen;
    makeDestSA(&yourSocketAddress, machine, port);

    char char_array[10001];

    unsigned long current_length = 0;
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
      printf("Current Sent Total = %lu.\n", current_length);

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

      printf("Current Received Total %lu.\n", current_length);
    }
    printf("%s", "Message Sent. ");
    printf("Current %lu.\n", current_length);
  }

  bool DoOperation(char *machine, int port, char message[]) {
    printf("%s.\n", "Start of DoOperation");
    struct sockaddr_in yourSocketAddress, peerSocketAddress;
    socklen_t peerAddrlen;
    makeDestSA(&yourSocketAddress, machine, port);

    char char_array[10001];

    unsigned long current_length = 0;
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
      printf("Current Sent Total = %lu.\n", current_length);

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

      printf("Current Received Total %lu.\n", current_length);
    }
    printf("%s", "Message Sent. ");
    printf("Current %lu.\n", current_length);
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

  int sign_up(string username, string password) {
    bool nospecial = true;
    for (int i = 0; i < username.length() && nospecial; i++) {
      nospecial = isalnum(username[i]);
      if (!nospecial)
        cout << username[i] << endl;
    }
    for (int i = 0; i < password.length() && nospecial; i++) {
      nospecial = isalnum(password[i]);
      if (!nospecial)
        cout << password[i] << endl;
    }
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {
      struct sockaddr_in yourSocketAddress, peerSocketAddress;
      socklen_t peerAddrlen;
      makeDestSA(&yourSocketAddress, dos_ip, dos_port);

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));
      string marshalled_massage_s = "1001" + username + "*" + password;
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      // Send Image Length

      /*while (received_length != strlen(message)) {
        received_length = 0;
        sprintf((char *)little_buffer, "%lu", strlen(message));
      */
      if ((n = sendto(sc->s, marshalled_massage,
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&yourSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout
      peerAddrlen = sizeof(peerSocketAddress);

      int n;

      struct pollfd ss;
      ss.fd = sc->s;
      ss.events = POLLIN;
      n = poll(&ss, 1, 1);
      if (n == 0 || n == -1) {
        // printf("Timeout!!\n");
        return 2;
      }

      else {
        unsigned char little_buffer[10];
        memset(little_buffer, 0, sizeof(little_buffer));
        if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                          (struct sockaddr *)&peerSocketAddress,
                          &peerAddrlen)) < 0)
          perror("Receive Failed");
        if (little_buffer[0] == '1')
          return 1;
        else if (little_buffer[0] == '0')
          return 5;
        else
          return 8;
      }

      /*
            // Change to unsigned long
            for (int i = 0; i < 10 && little_buffer[i] != '\0'; i++) {
              received_length *= 10;
              received_length += little_buffer[i] - '0';
            }
          }
      */
    }
    // cout << "End of sign_up.\n";
  }

  int login(string username, string password) {
    bool nospecial = true;
    for (int i = 0; i < username.length() && nospecial; i++) {
      nospecial = isalnum(username[i]);
      if (!nospecial)
        cout << username[i] << endl;
    }
    for (int i = 0; i < password.length() && nospecial; i++) {
      nospecial = isalnum(password[i]);
      if (!nospecial)
        cout << password[i] << endl;
    }
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {
      struct sockaddr_in yourSocketAddress, peerSocketAddress;
      socklen_t peerAddrlen;
      makeDestSA(&yourSocketAddress, dos_ip, dos_port);

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));
      string marshalled_massage_s = "1002" + username + "*" + password;
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      if ((n = sendto(sc->s, marshalled_massage,
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&yourSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout
      peerAddrlen = sizeof(peerSocketAddress);

      int n;

      struct pollfd ss;
      ss.fd = sc->s;
      ss.events = POLLIN;
      n = poll(&ss, 1, 1);
      if (n == 0 || n == -1) {
        // printf("Timeout!!\n");
        return 2;
      } else {
        unsigned char little_buffer[10];
        memset(little_buffer, 0, sizeof(little_buffer));
        if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                          (struct sockaddr *)&peerSocketAddress,
                          &peerAddrlen)) < 0)
          perror("Receive Failed");
        if (little_buffer[0] == '1')
          return 1;
        else if (little_buffer[0] == '0')
          return 0;
        else if (little_buffer[0] == '5')
          return 5;
        else if (little_buffer[0] == '4')
          return 4;
        else
          return 8;
      }
    }
  }



map<string, vector<string>> getUsers() {


      struct sockaddr_in yourSocketAddress, peerSocketAddress;
      socklen_t peerAddrlen;
      makeDestSA(&yourSocketAddress, dos_ip, dos_port);

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));
      string marshalled_massage_s = "1100";
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      if ((n = sendto(sc->s, marshalled_massage,
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&yourSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout
      peerAddrlen = sizeof(peerSocketAddress);

      int n;

      struct pollfd ss;
      ss.fd = sc->s;
      ss.events = POLLIN;
      n = poll(&ss, 1, 1);


        unsigned char little_buffer[LITTLE_BUFFER_SIZE];
        memset(little_buffer, 0, sizeof(little_buffer));
        if ((r = recvfrom(sc->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                          (struct sockaddr *)&peerSocketAddress,
                          &peerAddrlen)) < 0)
          perror("Receive Failed");
        int cc = 0;
        string temp;
        while (little_buffer[cc] != 0) {
                temp.append(1, little_buffer[cc]);
                cc++;
              }

        return retmap(temp);
    }

map <string, vector<string>> retmap (string s ){

    map <string, vector<string>> mymap;

    while(s!=""){

        int len = s.find ("*");

        string name = s.substr(0, len);

        s=s.erase(0, len+1);

        while (s[0]!='@'){

            int imgl = s.find("#");

            string img = s.substr(0, imgl);

            s=s.erase(0, imgl+1);

            mymap[name].push_back(img);

        }

        s= s.erase(0,1);

    }

    return mymap;

}

};

#endif
