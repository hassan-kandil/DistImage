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
#include <thread>
#include <unistd.h>
//#include "UDPSocketServer.h"
#include <QProcess>
#include <arpa/inet.h>
#include <fstream>
#include <locale>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

#define BUFFER_SIZE 50000

#ifndef PEER_H
#define PEER_H
#define LITTLE_BUFFER_SIZE 50000

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

using namespace std;

class Peer {
private:
  char sender_ip[INET_ADDRSTRLEN];
  uint16_t sender_port;

public:
  UDPSocketClient *sv; // UDPSocketServer *sv;
  char *dos_ip;
  int dos_port;
  UDPSocketClient *sc;
  struct sockaddr_in dosSocket;

  int n;

  string username, password;
  unsigned char buffer[BUFFER_SIZE];
  int r;
  struct sockaddr_in recievedAddr;
  socklen_t addresslength = sizeof(recievedAddr);
  vector<pair<int,pair<string, string>>> requests_buffer; // user, image

  unsigned char Serverbuffer[BUFFER_SIZE];
  unsigned char Serverlittle_buffer[LITTLE_BUFFER_SIZE];
  Peer() {
    this->sv = new UDPSocketClient(); // UDPSocketServer(0); // dos_port
    this->sc = new UDPSocketClient();

    //requests_buffer.push_back(make_pair("Test user","hi"));
  }
  ~Peer() {}

  static std::string base64_encode(unsigned char const *bytes_to_encode,
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

  void listenPeer() {
    cout << "Ana Henaaaa Thread ba listen!! " << endl;
    while (true) {
      getRequest();
    }
  }

  // Server Functions Start HEREEE

  static std::string base64_decode(std::string const &encoded_string) {
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

      char_array_3[0] =
          (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] =
          ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

      for (j = 0; (j < i - 1); j++)
        ret += char_array_3[j];
    }

    return ret;
  }

  void getRequest() {

    cout << this->username << " user starts get request:" << endl;
    // unsigned long current_received = 0;

    memset(Serverbuffer, 0, sizeof(Serverbuffer));
    // Receive Marshalled Message

    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);
    if ((r = recvfrom(sv->s, Serverbuffer, BUFFER_SIZE, 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) < 0)

      cout << "Received Message = %s.\n" << Serverbuffer;

    inet_ntop(AF_INET, &(tempSocketAddress.sin_addr), sender_ip,
              INET_ADDRSTRLEN);

    sender_port = htons((&tempSocketAddress)->sin_port);

    // printf("Thread re IP:%s & port: %d\n", sender_ip, sender_port);

    // Get operation ID as unsigned long
    unsigned long op_id = 0;
    for (int i = 0; i < 4 && Serverbuffer[i] != '\0'; i++) {
      op_id *= 10;
      op_id += Serverbuffer[i] - '0';
      // cout << op_id << endl;
    }

    switch (op_id) {

    case 2002: // view request
    {
      cout << "2002 request recieved" << endl;
      int cc = 4;
      string username = "", imageName = "";
      while (Serverbuffer[cc] != '*') {
        username.append(1, Serverbuffer[cc]);
        cc++;
      }
      cc++;
      while (Serverbuffer[cc] != '*') {
        imageName.append(1, Serverbuffer[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Requested Image Name: " << imageName << endl;
      requests_buffer.push_back(make_pair(2002, make_pair(username,imageName)));
      bool didApprove = true;
      // bool didApprove = grantRequest( username, imageName);
      // View Request reply
      memset(Serverlittle_buffer, 0, sizeof(Serverlittle_buffer));
      if (didApprove) {
        // sendImageThread(sender_ip, sender_port, imageName);
        Serverlittle_buffer[0] = '1';
      } else {
        Serverlittle_buffer[0] = '0';
      }
      // sprintf((char *)(Serverlittle_buffer), "%d", didsign);
      Serverlittle_buffer[1] = 0;
      if (sendto(sv->s, Serverlittle_buffer,
                 strlen((const char *)Serverlittle_buffer), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("View Request reply sendto failed");
      }

    } break; // end of view

    case 2003: // view approved
    {
      cout << "2003 request recieved" << endl;
      int cc = 4;
      string username = "", imageName = "";
      while (Serverbuffer[cc] != '*') {
        username.append(1, Serverbuffer[cc]);
        cc++;
      }
      cc++;
      while (Serverbuffer[cc] != '*') {
        imageName.append(1, Serverbuffer[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Approved Image Name: " << imageName << endl;
      requests_buffer.push_back(make_pair(2003, make_pair(username,imageName)));
      bool didApprove = true;
      // bool didApprove = grantRequest( username, imageName);
      // View Request reply
      memset(Serverlittle_buffer, 0, sizeof(Serverlittle_buffer));
      if (didApprove) {
        // sendImageThread(sender_ip, sender_port, imageName);
        Serverlittle_buffer[0] = '1';
      } else {
        Serverlittle_buffer[0] = '0';
      }
      // sprintf((char *)(Serverlittle_buffer), "%d", didsign);
      Serverlittle_buffer[1] = 0;
      if (sendto(sv->s, Serverlittle_buffer,
                 strlen((const char *)Serverlittle_buffer), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("View Request reply sendto failed");
      }

       // image length
      printf("%s.\n", "Start of image receive");
      unsigned char little_buffer[20000];
        unsigned long current_received = 0;
        memset(buffer, 0, sizeof(buffer));
        std::ofstream os("new_2.jpeg");
        memset(little_buffer, 0, sizeof(little_buffer));
        // Receive Image Length
        //struct sockaddr_in tempSocketAddress;
        //socklen_t tempAddrlen = sizeof(tempSocketAddress);
        r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0, (struct sockaddr *)&tempSocketAddress, &tempAddrlen);
        //printf("Received Length of Encoded Message (char[]) = %s.\n", little_buffer);

        // Change to unsigned long
        unsigned long received_length = 0;
        for(int i=0; i<LITTLE_BUFFER_SIZE && little_buffer[i]!='\0'; i++){
          received_length *= 10;
          received_length += little_buffer[i] - '0';
        }

        // Reply with Length
        memset(little_buffer, 0, sizeof(little_buffer));
        sprintf((char*)(little_buffer), "%lu", received_length);
        if (sendto(sv->s, little_buffer, strlen((const char*)little_buffer), 0, (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
          perror("length reply sendto failed");
        }

        cout << "Received Length of Encoded Message = " << received_length << ".\n";

        // Start Receiving Image
        while(current_received < received_length){
          //printf("%s\n", "Loop Start:");
            cout << "Loop Start:" << endl;
          memset(little_buffer, 0, sizeof(little_buffer));

          r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0, (struct sockaddr *)&tempSocketAddress, &tempAddrlen);

          current_received += r;
          //printf("Received total %lu encoded bytes.\n", current_received);
          cout << "Received total " << current_received << " encoded bytes.\n";
          std::string sName(reinterpret_cast<char*>(little_buffer));
          string y = base64_decode(sName);

          if (r > 0)  os << y;
          memset(little_buffer, 0, sizeof(little_buffer));
          sprintf((char*)(little_buffer), "%lu", current_received);

          if (sendto(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0, (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
                perror("sendto failed");
          }
          }
        os.close();
      /*
        // Steganography
          string extract_command, defaultPath = "default.jpeg";
          extract_command = "steghide extract -sf " + defaultPath+ " -p hk";
          int n = extract_command.length();
        char char_array[n+1];

        strcpy(char_array, extract_command.c_str());
          system(char_array);
      */
    } break; // end of view

    default:



      break;
    }
  }

  void sendReply() {
    struct sockaddr_in recievedAddr;
    socklen_t addresslength = sizeof(recievedAddr);
    if (sendto(sv->s, buffer, r, 0, (struct sockaddr *)&recievedAddr,
               addresslength) < 0) {
      perror("sendto failed");
    }
  }

  // End of Server Functions
/*
  static void sendImage(Peer *p, string privatePath, string name, int port) {

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
      p->DoOperation(my_name, port, char_array);
    } else
      cout << "could'nt open file" << endl;
  }

  bool sendImageThread(string hostname, int port, string imageName) {

    std::thread t1(sendImage, this, move(imageName), move(hostname),
                   move(port));
    t1.detach();
  }

  bool DoOperation(char *machine, int port, char message[]) {
    // printf("%s.\n", "Start of DoOperation");
    struct sockaddr_in yourSocketAddress, peerSocketAddress;
    socklen_t peerAddrlen;
    makeDestSA(&yourSocketAddress, machine, port);

    char char_array[10001];

    unsigned long current_length = 0;
    int r = 1;
    unsigned char little_buffer[10];
    memset(little_buffer, 0, sizeof(little_buffer));

    // printf("Length of Encoded Message = %lu.\n", strlen(message));

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

    // printf("Received Length of Encoded Message = %s.\n", little_buffer);
    unsigned long fakka = strlen(message) % 10000; // last image chunk

    // Start Sending Image
    while (current_length <
           strlen(message)) { //  && r == 1 && little_buffer[0] == '1'
      // printf("%s\n", "Loop Start:");
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
      // printf("Current Sent Total = %lu.\n", current_length);

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

      // printf("Current Received Total %lu.\n", current_length);
    }
    // printf("%s", "Message Sent. ");
    // printf("Current %lu.\n", current_length);
  }
*/


  static void makeDestSA(struct sockaddr_in *sa, char *hostname, int port) {
    struct hostent *host;
    sa->sin_family = AF_INET;
    if ((host = gethostbyname(hostname)) == NULL) {
      // printf("Unknown host name\n");
      exit(-1);
    }
    sa->sin_addr = *(struct in_addr *)(host->h_addr);
    sa->sin_port = htons(port);
  }

  int sign_up(string username, string password) {
    bool nospecial = true;
    for (int i = 0; i < username.length() && nospecial; i++) {
      nospecial = isalnum(username[i]);
    }
    for (int i = 0; i < password.length() && nospecial; i++) {
      nospecial = isalnum(password[i]);
    }
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {
      struct sockaddr_in dosSocketAddress;
      makeDestSA(&dosSocketAddress, dos_ip, dos_port);

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));
      string marshalled_massage_s = "1001" + username + "*" + password;
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      if ((n = sendto(sc->s, marshalled_massage,
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&dosSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout

      struct pollfd ss;
      ss.fd = sc->s;
      ss.events = POLLIN;
      int npoll = poll(&ss, 1, 1);
      if (npoll == 0 || npoll == -1) {
        ////printf("Timeout!!\n");
        return 2;
      }

      else {
        unsigned char little_buffer[10];
        memset(little_buffer, 0, sizeof(little_buffer));
        struct sockaddr_in tempSocketAddress;
        socklen_t tempAddrlen = sizeof(tempSocketAddress);
        if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                          (struct sockaddr *)&tempSocketAddress,
                          &tempAddrlen)) < 0)
          perror("Receive Failed");
        if (little_buffer[0] == '1')
          return 1;
        else if (little_buffer[0] == '0')
          return 5;
        else
          return 8;
      }
    }
  }

  int login(string username, string password) {
    bool nospecial = true;
    for (int i = 0; i < username.length() && nospecial; i++) {
      nospecial = isalnum(username[i]);
    }
    for (int i = 0; i < password.length() && nospecial; i++) {
      nospecial = isalnum(password[i]);
    }
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {

      makeDestSA(&(this->dosSocket), dos_ip, dos_port); // make dos socket

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));

      /*struct sockaddr_in peeraddr;
      socklen_t peeraddrlen = sizeof(peeraddr);
      getpeername(this->sv->s, (sockaddr*)&peeraddr, &peeraddrlen);

      int sv_port_d = ntohs(peeraddr.sin_port);
      cout << "sv_port_d " << sv_port_d << endl;
      string sv_port = to_string(sv_port_d);*/
      string marshalled_massage_s =
          "1002" + username + "*" + password; // + "*" + sv_port;
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      if ((n = sendto(sv->s, marshalled_massage, // sc->s
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&(this->dosSocket),
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout

      struct pollfd ss;
      ss.fd = sv->s;
      ss.events = POLLIN;
      int npoll = poll(&ss, 1, 1);
      if (npoll == 0 || npoll == -1) {
        ////printf("Timeout!!\n");
        return 2;
      } else {
        unsigned char little_buffer[10];
        memset(little_buffer, 0, sizeof(little_buffer));
        struct sockaddr_in tempSocketAddress;
        socklen_t tempAddrlen = sizeof(tempSocketAddress);
        if ((r = recvfrom(sv->s, little_buffer, 10, 0, // sc->s
                          (struct sockaddr *)&tempSocketAddress,
                          &tempAddrlen)) < 0)
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

  int logout() {

    char marshalled_massage[BUFFER_SIZE];
    memset(marshalled_massage, 0, sizeof(marshalled_massage));
    string marshalled_massage_s = "1003" + this->username;
    for (int j = 0; j < marshalled_massage_s.length(); j++) {
      marshalled_massage[j] = marshalled_massage_s[j];
    }
    marshalled_massage[marshalled_massage_s.length()] = 0;

    int r = 1;

    if ((n = sendto(sc->s, marshalled_massage,
                    strlen((const char *)marshalled_massage), 0,
                    (struct sockaddr *)&(this->dosSocket),
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    // Receive Timeout

    struct pollfd ss;
    ss.fd = sc->s;
    ss.events = POLLIN;
    int npoll = poll(&ss, 1, 1);
    if (npoll == 0 || npoll == -1) {
      ////printf("Timeout!!\n");
      return 2;
    } else {
      unsigned char little_buffer[10];
      memset(little_buffer, 0, sizeof(little_buffer));
      struct sockaddr_in tempSocketAddress; //////////////////
      socklen_t tempAddrlen = sizeof(tempSocketAddress);
      if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                        (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
          0)
        perror("Receive Failed");
      if (little_buffer[0] == '1')
        return 1;
      else
        return 0;
    }
  }

  int upload(string pathname, string imagename, string defaultimage) {
    if (pathname == "" || imagename == "" || defaultimage == "")
      return 6;
    bool nospecial = true;
    /*for (int i = 0; i < imagename.length() && nospecial; i++) {
      nospecial = isalnum(imagename[i]) || imagename[i] == '.' || imagename[i]
    == '/';
    }
    for (int i = 0; i < defaultimage.length() && nospecial; i++) {
      nospecial = isalnum(defaultimage[i]) || defaultimage[i] == '.' ||
    imagename[i] == '/';
    }*/
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {

      char marshalled_massage[BUFFER_SIZE];
      memset(marshalled_massage, 0, sizeof(marshalled_massage));
      string marshalled_massage_s =
          "2001" + this->username + "*" + pathname + "/" + imagename;
      for (int j = 0; j < marshalled_massage_s.length(); j++) {
        marshalled_massage[j] = marshalled_massage_s[j];
      }
      marshalled_massage[marshalled_massage_s.length()] = 0;

      int r = 1;

      if ((n = sendto(sc->s, marshalled_massage,
                      strlen((const char *)marshalled_massage), 0,
                      (struct sockaddr *)&(this->dosSocket),
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout

      struct pollfd ss;
      ss.fd = sc->s;
      ss.events = POLLIN;
      int npoll = poll(&ss, 1, 1);
      if (npoll == 0 || npoll == -1) {
        return 2; ////printf("Timeout!!\n");
      } else {
        unsigned char little_buffer[10];
        memset(little_buffer, 0, sizeof(little_buffer));
        struct sockaddr_in tempSocketAddress;
        socklen_t tempAddrlen = sizeof(tempSocketAddress);
        if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                          (struct sockaddr *)&tempSocketAddress,
                          &tempAddrlen)) < 0)
          perror("Receive Failed");
        if (little_buffer[0] == '1') {

          QProcess::execute(
              QString::fromStdString("cp " + pathname + "/" + defaultimage +
                                     " " + pathname + "/s" + imagename));

          QProcess::execute(QString::fromStdString(
              "steghide embed -cf " + pathname + "/s" + imagename + " -ef " +
              pathname + "/" + imagename + " -p hk "));

          return 1;

        } else
          return 0;
      }
    }
  }
  /*
    string modify_image_to_default(string x) {
      string y;

      for (int i = x.length() - 1; i > 0; i--) {

        if (x[i] == '/') {

          y = x.substr(0, i);
          break;
        }
      }

      y = y + "/default.jpeg";

      return y;
    }
  */

  void request_image(string selectedUser, string selectedImage,
                     string path_full) {

    map<string, vector<string>> users;
    users = this->getUsers();
    vector<string> images;
    images = users[selectedUser];
    struct sockaddr_in ownerSocket;

    string temp_ip = images[1];
    int remote_peer_port = std::stoi(images[2], nullptr, 0); // Refaay
    cout << "Remote IP " << temp_ip << ", port " << remote_peer_port << endl;
    char remote_peer_address[1024];
    strcpy(remote_peer_address, temp_ip.c_str());

    makeDestSA(&ownerSocket, remote_peer_address, remote_peer_port);

    char marshalled_massage[BUFFER_SIZE];
    memset(marshalled_massage, 0, sizeof(marshalled_massage));
    string image_with_full_path = path_full + "/" + selectedImage;
    string marshalled_massage_s =
        "2002" + this->username + "*" + image_with_full_path + "*";

    for (int j = 0; j < marshalled_massage_s.length(); j++) {
      marshalled_massage[j] = marshalled_massage_s[j];
    }
    marshalled_massage[marshalled_massage_s.length()] = 0;

    int r = 1;

    if ((n = sendto(sc->s, marshalled_massage,
                    strlen((const char *)marshalled_massage), 0,
                    (struct sockaddr *)&ownerSocket,
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");
  }

  void send_image(string selectedUser, string selectedImage,
                     string path_full) {
      //peer->send_image(usname, imname, path);
    map<string, vector<string>> users;
    users = this->getUsers();
    vector<string> images;
    images = users[selectedUser];
    struct sockaddr_in receiverSocket;

    string temp_ip = images[1];
    int remote_peer_port = std::stoi(images[2], nullptr, 0); // Refaay
    cout << "Remote IP " << temp_ip << ", port " << remote_peer_port << endl;
    char remote_peer_address[1024];
    strcpy(remote_peer_address, temp_ip.c_str());

    makeDestSA(&receiverSocket, remote_peer_address, remote_peer_port);

    char marshalled_massage[BUFFER_SIZE];
    memset(marshalled_massage, 0, sizeof(marshalled_massage));
    string image_with_full_path = path_full + "/" + selectedImage;
    string marshalled_massage_s =
        "2003" + this->username + "*" + image_with_full_path + "*";

    for (int j = 0; j < marshalled_massage_s.length(); j++) {
      marshalled_massage[j] = marshalled_massage_s[j];
    }
    marshalled_massage[marshalled_massage_s.length()] = 0;

    int r = 1;

    if ((n = sendto(sc->s, marshalled_massage,
                    strlen((const char *)marshalled_massage), 0,
                    (struct sockaddr *)&receiverSocket,
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    // Send the image
    //bool DoOperation(char *machine, int port, char message[]){
            printf("%s.\n", "Start of Send image");
            //struct sockaddr_in yourSocketAddress, peerSocketAddress;
            //socklen_t peerAddrlen;
            //makeDestSA(&yourSocketAddress,machine, port);




              std::ifstream is (image_with_full_path, std::ifstream::binary);

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
                char message[n+1];
                    strcpy(message, x.c_str());

                // start of dooperation

                char char_array[10001];

                int current_length = 0;
                r = 1;
                unsigned char little_buffer[10];
                memset(little_buffer, 0, sizeof(little_buffer));

                printf("Length of Encoded Message = %lu.\n", strlen(message));

                // Send Image Length
                unsigned long received_length = 0;
                struct sockaddr_in tempSocketAddress;
                socklen_t tempAddrlen = sizeof(tempSocketAddress);
                while(received_length != strlen(message)){ // != strlen(message)
                    received_length = 0;
                    sprintf((char*)little_buffer, "%lu", strlen(message));

                    if( (n = sendto(sc->s, little_buffer, strlen((const char*)little_buffer), 0, (struct sockaddr *) &receiverSocket, sizeof(struct sockaddr_in))) < 0)
                    perror("Send failed\n");

                    if((r = recvfrom(sc->s, little_buffer, 10, 0, (struct sockaddr *) &tempSocketAddress,  &tempAddrlen))<0)
                        perror("Receive Failed") ;

                    // Change to unsigned long
                  for(int i=0; i<10 && little_buffer[i]!='\0'; i++){
                    received_length *= 10;
                    received_length += little_buffer[i] - '0';
                  }

                }

                printf("Received Length of Encoded Message = %s.\n", little_buffer);
                unsigned long fakka = strlen(message) % 10000; // last image chunk

                // Start Sending Image
                while (current_length < strlen(message)){ //  && r == 1 && little_buffer[0] == '1'
                    printf("%s\n", "Loop Start:");
                    if (current_length + 10000 < strlen(message)){
                        memcpy (char_array, message+(current_length), 10000);
                        current_length+=10000;
                        char_array[10000] = 0;
                    }
                    else{
                        memcpy (char_array, message+(current_length), fakka);
                        current_length+=fakka;
                        char_array[fakka] = 0; // C-String terminate
                    }
                    if( (n = sendto(sc->s, char_array, strlen(char_array), 0, (struct sockaddr *) &receiverSocket, sizeof(struct sockaddr_in))) < 0)
                    perror("Send failed\n");
                    printf("Current Sent Total = %d.\n", current_length);

                    memset(little_buffer, 0, sizeof(little_buffer));
                    if((r = recvfrom(sc->s, little_buffer, 10, 0, (struct sockaddr *) &tempSocketAddress,  &tempAddrlen))<0)
                        perror("Receive Failed") ;
                    // Change to unsigned long
                  received_length = 0;
                  for(int i=0; i<10 && little_buffer[i]!='\0'; i++){
                    received_length *= 10;
                    received_length += little_buffer[i] - '0';
                  }

                    if(received_length != current_length){
                        perror("Dropped packets! received_length != current_length.");
                        current_length = received_length; // Drop Tolerance
                    }

                    printf("Current Received Total %d.\n", current_length);
                }
                printf("%s", "Message Sent. ");
                printf("Current %d.\n", current_length);

              }
              else
                cout << "could'nt open file" << endl;



  }


  map<string, vector<string>> getUsers() {

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
                    (struct sockaddr *)&(this->dosSocket),
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    // Receive Timeout
    cout << "getusers sent" << endl;
    unsigned char little_buffer[LITTLE_BUFFER_SIZE];
    memset(little_buffer, 0, sizeof(little_buffer));
    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);
    if ((r = recvfrom(sc->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) < 0)
      perror("Receive Failed");
    cout << "getusers received" << endl;
    int cc = 0;
    string temp;
    while (little_buffer[cc] != 0) {
      temp.append(1, little_buffer[cc]);
      cc++;
    }

    return retmap(temp);
  }

  map<string, vector<string>> retmap(string s) {
    map<string, vector<string>> mymap;
    while (s != "") {
      int len = s.find("*");
      string name = s.substr(0, len);
      s = s.erase(0, len + 1);
      int onlineln = s.find("&");
      string online = s.substr(0, onlineln);
      s = s.erase(0, onlineln + 1);
      int ipln = s.find("&");
      string ip = s.substr(0, ipln);
      s = s.erase(0, ipln + 1);
      int portln = s.find("&");
      string port = s.substr(0, portln);
      s = s.erase(0, portln + 1);
      mymap[name].push_back(online);
      mymap[name].push_back(ip);
      mymap[name].push_back(port);
      while (s[0] != '@') {
        int imgl = s.find("#");
        string img = s.substr(0, imgl);
        s = s.erase(0, imgl + 1);
        mymap[name].push_back(img);
      }
      s = s.erase(0, 1);
    }
    return mymap;
  }
};

#endif
