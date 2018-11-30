#include "Message.h"
#include "UDPSocketClient.h"
#include <QProcess>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std;
//#include <limits.h> // for getcwd
#define BUFFER_SIZE 50000

#ifndef PEER_H
#define PEER_H
#define LITTLE_BUFFER_SIZE 50000

using namespace std;

class Peer {
private:
  char sender_ip[INET_ADDRSTRLEN];
  uint16_t sender_port;

public:
  UDPSocketClient *sv;
  //  UDPSocketServer *sv;
  char *dos_ip;
  int dos_port;
  UDPSocketClient *sc;
  struct sockaddr_in dosSocket;
  int requestID = 0;

  int n;

  string username, password;
  unsigned char buffer[BUFFER_SIZE];
  int r;
  struct sockaddr_in recievedAddr;
  socklen_t addresslength = sizeof(recievedAddr);
  vector<pair<int, pair<string, string>>>
      requests_buffer; // <request_code, <user, image>>

  unsigned char Serverbuffer[BUFFER_SIZE];
  unsigned char Serverlittle_buffer[LITTLE_BUFFER_SIZE];

  map<string, vector<string>> users;
  map<string, vector<string>>::iterator it;

  Peer() {
    this->sv = new UDPSocketClient(); // UDPSocketServer(0); // dos_port
    this->sc = new UDPSocketClient();
  }
  ~Peer() {}

  void listenPeer() {
    cout << "Ana Henaaaa Thread ba listen!! " << endl;
    while (true) {
      getRequest();
    }
  }

  // Server Functions Start HEREEE

  void getRequest() {

    cout << " user starts get request:" << endl;

    memset(Serverbuffer, 0, sizeof(Serverbuffer));
    // Receive Marshalled Message
    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);
    if ((r = recvfrom(sv->s, Serverbuffer, BUFFER_SIZE, 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
        0) {
      cout << "Receive Failed! " << endl;
    }

    cout << "r  " << r << endl;

    inet_ntop(AF_INET, &(tempSocketAddress.sin_addr), sender_ip,
              INET_ADDRSTRLEN);

    sender_port = htons((&tempSocketAddress)->sin_port);

    Message requestMsg(reinterpret_cast<char *>(Serverbuffer));
    int op_id_request = requestMsg.getOperation();
    int rpcid_request = requestMsg.getRPCId();
    //    size_t msgsize = requestMsg.getMessageSize();
    string msg = requestMsg.getUnmarshalledMessage();

    switch (op_id_request) {

    case 2002: // view request
    {
      cout << "2002 request recieved" << endl;
      int cc = 0;
      string username = "", imageName = "";
      while (msg[cc] != '*') {
        username.append(1, msg[cc]);
        cc++;
      }
      cc++;
      while (msg[cc] != '*') {
        imageName.append(1, msg[cc]);
        cc++;
      }

      cout << "User: " << username << endl;
      cout << "Requested Image Name: " << imageName << endl;

      memset(Serverlittle_buffer, 0, sizeof(Serverlittle_buffer));

      pair<int, pair<string, string>> pair_temp =
          make_pair(2002, make_pair(username, imageName));
      bool pair_found = false;
      for (int e = 0; e < requests_buffer.size() && !pair_found; e++) {
        pair_found = requests_buffer[e] == pair_temp;
      }
      if (!pair_found) {
        requests_buffer.push_back(pair_temp);
        Serverlittle_buffer[0] = '1';
      } else {
        Serverlittle_buffer[0] = '0';
      }

      Serverlittle_buffer[1] = 0;

      char *msg_char = reinterpret_cast<char *>(this->Serverlittle_buffer);

      Message view_request_reply(Reply, msg_char, strlen(msg_char),
                                 op_id_request, rpcid_request, 0, 0, 0);
      string x_reply = view_request_reply.marshal();
      char marshalled_message_reply[BUFFER_SIZE];
      int n = x_reply.length();
      strncpy(marshalled_message_reply, x_reply.c_str(), n + 1);

      if (sendto(sv->s, marshalled_message_reply,
                 strlen((const char *)marshalled_message_reply), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("View Request reply sendto failed");
      }

      // End of changes

    } break; // end of view

    case 2003: // view approved
    {
      cout << "2003 request by owner to send the image recieved" << endl;
      int cc = 0;
      string username = "", imageName = "";
      while (msg[cc] != '*') {
        username.append(1, msg[cc]);
        cc++;
      }
      cc++;
      while (msg[cc] != '*') {
        imageName.append(1, msg[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Approved Image Name: " << imageName << endl;
      requests_buffer.push_back(
          make_pair(2003, make_pair(username, imageName)));

      // Hassan Changes
      // this->sendReply(reinterpret_cast<char*>(this->Serverbuffer));

      // Marshal the reply and then send it
      char *msg_char = reinterpret_cast<char *>(this->Serverbuffer);

      Message login_request_reply(Reply, msg_char, strlen(msg_char),
                                  op_id_request, rpcid_request, 0, 0, 0);

      string x_reply = login_request_reply.marshal();

      char marshalled_message_reply[BUFFER_SIZE];

      int n = x_reply.length();
      strncpy(marshalled_message_reply, x_reply.c_str(), n + 1);

      if (sendto(sv->s, marshalled_message_reply,
                 strlen(marshalled_message_reply), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("send to reply failed");
      }

      // End of changes

    } break; // end of view

    case 2004: // receive Image
    {
      // image length
      unsigned long current_received = 0;

      int fragd = requestMsg.getDidFrag();
      int MF = requestMsg.getMoreFrag();
      int fragc = requestMsg.getFragCount();
      int fraglength = requestMsg.getMessageSize();

      // string y(msg,fraglength);
      //
      //
      //   char * imfirstfrag = requestMsg.getMessage();
      cout << "Received Successfully!! " << endl;
      // cout<<Serverbuffer<<endl;
      cout << "Received Message Length = \n"
           << strlen((const char *)Serverbuffer);
      cout << "imfirstfrag length " << fraglength << endl;
      // this->sendReply(reinterpret_cast<char*>(this->Serverbuffer));

      // Hassan Changes

      current_received += r;
      unsigned char little_buffer[20000];

      memset(little_buffer, 0, sizeof(little_buffer));
      sprintf((char *)(little_buffer), "%lu", current_received);

      // Marshal the reply and then send it
      char *msg_char = reinterpret_cast<char *>(little_buffer);

      cout << "little_buffer " << little_buffer << endl;

      Message image_reply(Reply, msg_char, strlen(msg_char), op_id_request,
                          rpcid_request, fragd, fragc, MF);

      string x_reply = image_reply.marshal();

      char marshalled_message_reply[BUFFER_SIZE];

      int n = x_reply.length();
      strncpy(marshalled_message_reply, x_reply.c_str(), n + 1);

      cout << "marshalled_message_reply " << marshalled_message_reply << endl;

      if (sendto(sv->s, marshalled_message_reply,
                 strlen(marshalled_message_reply), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("send to reply failed");
      }

      printf("%s.\n", "Start of image receive");
      // std::ofstream os(
      //    "/home/hkandil/Downloads/distributed_pro-master-latest/new.jpeg");

      // refaay: should get ownername and imagename with the send
      // string steg_image_name = this->username + "_" + selectedImage;
      std::ofstream os("new.jpeg"); // refaay should change

      if (r > 0) {
        os << msg;
      }

      if (fragd) {

        // memset(buffer, 0, sizeof(buffer));
        memset(little_buffer, 0, sizeof(little_buffer));

        // Start Receiving Image
        while (MF) {
          cout << "Loop Start:" << endl;
          memset(little_buffer, 0, sizeof(little_buffer));

          r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                       (struct sockaddr *)&tempSocketAddress, &tempAddrlen);

          Message imageFrag(reinterpret_cast<char *>(little_buffer));

          string imfrag = imageFrag.getUnmarshalledMessage();
          int imfraglen = imageFrag.getMessageSize();
          int rpcid_new = imageFrag.getRPCId();
          int op_id_new = imageFrag.getOperation();
          int fragc_new = imageFrag.getFragCount();

          // string newY(imfrag,imfraglen);

          current_received += r;
          cout << "Received total " << current_received << " encoded bytes.\n";

          // Marshal the reply and then send it

          memset(little_buffer, 0, sizeof(little_buffer));
          sprintf((char *)(little_buffer), "%lu", current_received);

          char *msg_char = reinterpret_cast<char *>(little_buffer);

          Message image_reply(Reply, msg_char, strlen(msg_char), op_id_new,
                              rpcid_new, fragd, fragc_new, MF);

          string x_reply = image_reply.marshal();

          char marshalled_message_reply[BUFFER_SIZE];

          int n = x_reply.length();
          strncpy(marshalled_message_reply, x_reply.c_str(), n + 1);

          if (rpcid_request == rpcid_new && (fragc++) == fragc_new) {

            MF = imageFrag.getMoreFrag();

            if (r > 0) {
              os << imfrag;
            }

            if (sendto(sv->s, marshalled_message_reply,
                       strlen(marshalled_message_reply), 0,
                       (struct sockaddr *)&tempSocketAddress,
                       tempAddrlen) < 0) {
              perror("send to reply failed");
            }

            // End of changes

          } else if ((rpcid_request == rpcid_new) && (fragc == fragc_new)) {
            // Re-send the reply without writing the image
            // if the image fragment was sent before

            if (sendto(sv->s, marshalled_message_reply,
                       strlen(marshalled_message_reply), 0,
                       (struct sockaddr *)&tempSocketAddress,
                       tempAddrlen) < 0) {
              perror("send to reply failed");
            }
          }
        }
      }
      os.close();

      string extract_command, defaultPath = "new.jpeg";
      extract_command = "steghide extract -sf " + defaultPath + " -p hk";
      QProcess::execute(QString::fromStdString(extract_command));
      /*int nn = extract_command.length();
      char char_array[nn + 1];
      strcpy(char_array, extract_command.c_str());
      system(char_array);*/
    }

    default:

      break;
    }
  }

  void sendReply(char *temp_buffer) {

    struct sockaddr_in recievedAddr;
    socklen_t addresslength = sizeof(recievedAddr);
    if (sendto(sv->s, temp_buffer, strlen(temp_buffer), 0,
               (struct sockaddr *)&recievedAddr, addresslength) < 0) {
      perror("sendto failed");
    }
  }

  // End of Server Functions

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

      string msg = username + "*" + password;
      char *msg_char = new char[msg.length() + 1];
      strcpy(msg_char, msg.c_str());

      Message sign_up_request(Request, msg_char, strlen(msg_char), 1001,
                              requestID++, 0, 0, 0);

      char marshalled_message[BUFFER_SIZE];

      string x = sign_up_request.marshal();
      int n = x.length();
      strncpy(marshalled_message, x.c_str(), n + 1);

      int r = 1;

      if ((n = sendto(sc->s, marshalled_message,
                      strlen((const char *)marshalled_message), 0,
                      (struct sockaddr *)&dosSocketAddress,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      /*  // Receive Timeout

        struct pollfd ss;
        ss.fd = sc->s;
        ss.events = POLLIN;
        int npoll = poll(&ss, 1, 1);
        if (npoll == 0 || npoll == -1) {
          ////printf("Timeout!!\n");
          return 2;
        }

        else {*/
      unsigned char little_buffer[10];
      memset(little_buffer, 0, sizeof(little_buffer));
      struct sockaddr_in tempSocketAddress;
      socklen_t tempAddrlen = sizeof(tempSocketAddress);
      if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                        (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
          0)
        perror("Receive Failed");

      if (little_buffer[0] == '1')
        return 1;
      else if (little_buffer[0] == '0')
        return 5;
      else
        return 8;
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

      string msg = username + "*" + password;
      char *msg_char = new char[msg.length() + 1];
      strcpy(msg_char, msg.c_str());
      cout << msg_char << endl;

      Message login_request(Request, msg_char, strlen(msg_char), 1002,
                            requestID++, 0, 0, 0);
      //  char * marshalled_message = login_request.marshal();

      char marshalled_message[BUFFER_SIZE];

      string x = login_request.marshal();
      int n = x.length();
      strncpy(marshalled_message, x.c_str(), n + 1);

      int r = 1;

      if ((n = sendto(sv->s, marshalled_message, // sc->s
                      strlen((const char *)marshalled_message), 0,
                      (struct sockaddr *)&(this->dosSocket),
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      /*   // Receive Timeout

         struct pollfd ss;
         ss.fd = sv->s;
         ss.events = POLLIN;
         int npoll = poll(&ss, 1, 1);
         if (npoll == 0 || npoll == -1) {
           ////printf("Timeout!!\n");
           return 2;


         } else { */
      unsigned char little_buffer[10];
      memset(little_buffer, 0, sizeof(little_buffer));
      struct sockaddr_in tempSocketAddress;
      socklen_t tempAddrlen = sizeof(tempSocketAddress);
      if ((r = recvfrom(sv->s, little_buffer, 10, 0, // sc->s
                        (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
          0)
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

  int logout() {

    string msg = this->username;
    char *msg_char = new char[msg.length() + 1];
    strcpy(msg_char, msg.c_str());

    Message logout_request(Request, msg_char, strlen(msg_char), 1003,
                           requestID++, 0, 0, 0);
    // char * marshalled_message = logout_request.marshal();

    char marshalled_message[BUFFER_SIZE];

    string x = logout_request.marshal();
    int n = x.length();
    strncpy(marshalled_message, x.c_str(), n + 1);

    int r = 1;

    if ((n = sendto(sc->s, marshalled_message,
                    strlen((const char *)marshalled_message), 0,
                    (struct sockaddr *)&(this->dosSocket),
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    // Receive Timeout

    /*   struct pollfd ss;
       ss.fd = sc->s;
       ss.events = POLLIN;
       int npoll = poll(&ss, 1, 1);
       if (npoll == 0 || npoll == -1) {
         ////printf("Timeout!!\n");
         return 2;
       } else { */

    unsigned char little_buffer[10];
    memset(little_buffer, 0, sizeof(little_buffer));
    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);
    if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) < 0)
      perror("Receive Failed");
    if (little_buffer[0] == '1')
      return 1;
    else
      return 0;
  }

  int upload(string imagepath) {
    if (imagepath == "")
      return 6;

    string pathname, imagename;
    for (int j = imagepath.length() - 1; j > 0; j--) {

      if (imagepath[j] == '/') {
        pathname = imagepath.substr(0, j);
        imagename = imagepath.substr(j + 1, imagepath.length() - 1);
        break;
      }
    }
    bool nospecial = true;

    for (int i = 0; i < imagename.length() && nospecial; i++) {
      nospecial =
          isalnum(imagename[i]) || imagename[i] == '.' || imagename[i] == '/';
      if (!nospecial)
        cout << "Special char is " << imagename[i] << endl;
    }
    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {
      string msg = this->username + "*" + imagename;
      char *msg_char = new char[msg.length() + 1];
      strcpy(msg_char, msg.c_str());

      Message upload_request(Request, msg_char, strlen(msg_char), 2001,
                             requestID++, 0, 0, 0);

      //  char * marshalled_message = upload_request.marshal();

      char marshalled_message[BUFFER_SIZE];

      string x = upload_request.marshal();
      int n = x.length();
      strncpy(marshalled_message, x.c_str(), n + 1);

      int r = 1;

      if ((n = sendto(sc->s, marshalled_message,
                      strlen((const char *)marshalled_message), 0,
                      (struct sockaddr *)&(this->dosSocket),
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");

      // Receive Timeout

      //      struct pollfd ss;
      //      ss.fd = sc->s;
      //      ss.events = POLLIN;
      //      int npoll = poll(&ss, 1, 1);
      //      if (npoll == 0 || npoll == -1) {
      //        return 2; ////printf("Timeout!!\n");
      //      } else {
      unsigned char little_buffer[10];
      memset(little_buffer, 0, sizeof(little_buffer));
      struct sockaddr_in tempSocketAddress;
      socklen_t tempAddrlen = sizeof(tempSocketAddress);
      if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                        (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
          0)
        perror("Receive Failed");
      if (little_buffer[0] == '1') {

        QProcess::execute(QString::fromStdString(
            "cp " + pathname + "/default.jpeg " + pathname + "/" +
            this->username + "_" + imagename));

        QProcess::execute(QString::fromStdString(
            "steghide embed -cf " + pathname + "/" + this->username + "_" +
            imagename + " -ef " + pathname + "/" + imagename + " -p hk "));

        return 1;

      } else if (little_buffer[0] == '0') {
        return 0;
      } else if (little_buffer[0] == '9') {
        return 9;
      } else
        return 8;
    }
  }

  int request_image(string selectedUser, string selectedImage) {

    vector<string> images;
    images = this->users[selectedUser];
    struct sockaddr_in ownerSocket;

    string temp_ip = images[1];
    int remote_peer_port = std::stoi(images[2], nullptr, 0); // Refaay
    cout << "Remote IP " << temp_ip << ", port " << remote_peer_port << endl;
    char remote_peer_address[1024];
    char little_buffer[100];
    strcpy(remote_peer_address, temp_ip.c_str());

    makeDestSA(&ownerSocket, remote_peer_address, remote_peer_port);

    // string image_with_full_path = path_full + "/" + selectedImage;
    string msg = this->username + "*" + selectedImage + "*";
    char *msg_char = new char[msg.length() + 1];
    strcpy(msg_char, msg.c_str());

    Message image_request(Request, msg_char, strlen(msg_char), 2002,
                          requestID++, 0, 0, 0);
    //  char * marshalled_message = image_request.marshal();

    char marshalled_message[BUFFER_SIZE];

    string x = image_request.marshal();
    int n = x.length();
    strncpy(marshalled_message, x.c_str(), n + 1);

    if ((n = sendto(sc->s, marshalled_message,
                    strlen((const char *)marshalled_message), 0,
                    (struct sockaddr *)&ownerSocket,
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    memset(little_buffer, 0, sizeof(little_buffer));

    // Preparing a temp socket address to store the address of the receiver
    // sending the reply in
    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);

    if ((r = recvfrom(sc->s, little_buffer, sizeof(little_buffer), 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) <
        0) {
      cout << "Receive Failed! " << endl;
      return 3;
    } else {
      // unmarshal the reply
      Message reply_view_request(reinterpret_cast<char *>(little_buffer));

      string msg_view_request_reply =
          reply_view_request.getUnmarshalledMessage();

      cout << "msg_received_length " << msg_view_request_reply << endl;
      if (msg_view_request_reply[0] == '1')
        return 1;
      else if (msg_view_request_reply[0] == '0')
        return 0;
      else
        return 2;
    }

    /* Hassan's resend if lost
        int rpc_id_new = reply_view_request.getRPCId();


    if (rpc_id_new != requestID) // check if the request matches the reply
    {
      // if not resend the request
      if ((n = sendto(sc->s, marshalled_message,
                      strlen((const char *)marshalled_message), 0,
                      (struct sockaddr *)&ownerSocket,
                      sizeof(struct sockaddr_in))) < 0)
        perror("Send failed\n");
    }*/
  }

  void approve_image(string selectedUser, string selectedImage) {

    vector<string> images;
    images = this->users[selectedUser]; // Saving the vector of the selected
                                        // user image names & socket addresses
                                        // inside the variable images

    struct sockaddr_in
        receiverSocket; // instantiating the receiver socket address (the user
                        // who has requested my image)

    string remote_peer_ip = images[1]; // retriveing the ip of the receiver
    int remote_peer_port =
        std::stoi(images[2], nullptr,
                  0); // Refaay //Retreiving the port no of the receiver
    cout << "Remote IP " << remote_peer_ip << ", port " << remote_peer_port
         << endl;

    // Preparing the receiver (remote peer) socket address
    char remote_peer_address[1024];
    strcpy(remote_peer_address, remote_peer_ip.c_str());
    makeDestSA(&receiverSocket, remote_peer_address, remote_peer_port);

    // Sending a request to the receiver telling him to start receiving an image
    // Marshalling the message

    string msg = this->username + "*" + selectedImage + "*";
    char *msg_char = new char[msg.length() + 1];
    strcpy(msg_char, msg.c_str());

    Message sendimage_request(Request, msg_char, strlen(msg_char), 2003,
                              requestID++, 0, 0, 0);
    // char * marshalled_message = sendimage_request.marshal();

    char marshalled_message[BUFFER_SIZE];

    string x = sendimage_request.marshal();
    int n = x.length();
    strncpy(marshalled_message, x.c_str(), n + 1);

    int r = 1;

    if ((n = sendto(sc->s, marshalled_message,
                    strlen((const char *)marshalled_message), 0,
                    (struct sockaddr *)&receiverSocket,
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");

    // receive reply
    unsigned char little_buffer[10];
    memset(little_buffer, 0, sizeof(little_buffer));
    struct sockaddr_in tempSocketAddress;
    socklen_t tempAddrlen = sizeof(tempSocketAddress);
    if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                      (struct sockaddr *)&tempSocketAddress, &tempAddrlen)) < 0)
      perror("Receive Failed");
  }

  void send_image(string viewerName, string selectedImage) {
    UDPSocketClient *newSock = new UDPSocketClient();
    vector<string> images;
    images = this->users[viewerName]; // Saving the vector of the selected
                                      // user image names & socket addresses
                                      // inside the variable images

    struct sockaddr_in
        receiverSocket; // instantiating the receiver socket address (the user
                        // who has requested my image)

    string remote_peer_ip = images[1]; // retriveing the ip of the receiver
    int remote_peer_port =
        std::stoi(images[2], nullptr,
                  0); // Refaay //Retreiving the port no of the receiver
    cout << "Remote IP " << remote_peer_ip << ", port " << remote_peer_port
         << endl;

    // Preparing the receiver (remote peer) socket address
    char remote_peer_address[1024];
    strcpy(remote_peer_address, remote_peer_ip.c_str());
    makeDestSA(&receiverSocket, remote_peer_address, remote_peer_port);

    cout << "Start of Send image" << endl;
    string steg_image_name = this->username + "_" + selectedImage;
    cout << "Image name " << selectedImage << " Steg name " << steg_image_name
         << endl;
    /*
    // Refaay: Qt needs path to open image!
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      cout << "Current working dir: " << cwd << endl;
    } else {
      cout << "getcwd() error! Cannot get current path!" << endl;
      // return 1;
    }

    std::ifstream is(string(cwd) + "/" + steg_image_name,
                     std::ifstream::binary);*/
    std::ifstream is(steg_image_name, std::ifstream::binary);

    if (is) {

      // getting length of file
      is.seekg(0, is.end);
      unsigned int length = is.tellg();
      is.seekg(0, is.beg);
      // cout << "Original Decoded Image Length: "<< length << endl;

      char *newbuffer = new char[length]; // allocate memory

      is.read(newbuffer, length); // read data as a block
      cout << "buffer length " << length << endl;

      is.close();

      char char_array[10001];
      string x;
      int current_length = 0;
      int current_length_before_marshalling = 0;
      unsigned long fakka = length % 10000; // last image chunk

      unsigned char little_buffer[2000];
      memset(little_buffer, 0, sizeof(little_buffer));

      requestID++;
      int fragc = 0;
      int MF = 1;
      int fragd = 0;
      if (length > 10000)
        fragd = 1;

      // Preparing a temp socket address to store the address of the receiver
      // sending the reply in
      struct sockaddr_in tempSocketAddress;
      socklen_t tempAddrlen = sizeof(tempSocketAddress);

      char message[BUFFER_SIZE];
      char message_fakka[BUFFER_SIZE];

      // Start Sending Image
      while (current_length_before_marshalling < length) {
        printf("%s\n", "Loop Start:");
        if (current_length_before_marshalling + 10000 < length) {

          // memcpy (char_array, message+(current_length), 10000);

          // char_array[10000] = '\0';
          // cout<<"char_array "<<char_array<<endl;

          Message imageFrag(Request,
                            (newbuffer + current_length_before_marshalling),
                            10000, 2004, requestID, fragd, ++fragc, MF);

          x = imageFrag.marshal();
          int n = x.length();
          strncpy(message, x.c_str(), n + 1);
          current_length += n;
          current_length_before_marshalling += 10000;

          //  cout<<message<<endl;
          if ((n = sendto(newSock->s, message, strlen(message), 0,
                          (struct sockaddr *)&receiverSocket,
                          sizeof(struct sockaddr_in))) < 0)
            perror("Send failed\n");
          cout << "Current Sent: " << strlen(message) << endl;
          printf("Current Sent Total = %d.\n", current_length);

          memset(little_buffer, 0, sizeof(little_buffer));
          if ((r = recvfrom(newSock->s, little_buffer, sizeof(little_buffer), 0,
                            (struct sockaddr *)&tempSocketAddress,
                            &tempAddrlen)) < 0)
            perror("Receive Failed");
          cout << "received length before unmarshalling: " << little_buffer
               << endl;

          // unmarshal the reply
          Message reply_received_length(
              reinterpret_cast<char *>(little_buffer));

          string msg_received_length =
              reply_received_length.getUnmarshalledMessage();

          cout << "msg_received_length " << msg_received_length << endl;
          // Change to long
          long received_length = stol(msg_received_length);
          cout << "received_length " << received_length << endl;

          // checks if the total length of the packets sent is equal to the
          // received length in the reply

          if (received_length != current_length) {
            // if not reset the current_length_before_marshalling in order to
            // resend the packet
            perror("Dropped packets! received_length != current_length.");
            current_length_before_marshalling -= 10000; // Drop Tolerance
          }

          printf("Current Received Total %d.\n", current_length);

        } else {
          // memcpy (char_array, message+(current_length), fakka);

          // char_array[fakka] = '\0'; // C-String terminate

          MF = 0;
          Message imageLastFrag(Request,
                                (newbuffer + current_length_before_marshalling),
                                fakka, 2004, requestID, fragd, ++fragc, MF);
          x = imageLastFrag.marshal();
          int n = x.length();
          strncpy(message_fakka, x.c_str(), n + 1);
          current_length += n;
          current_length_before_marshalling += fakka;

          //  cout<<message<<endl;
          if ((n = sendto(sc->s, message_fakka, strlen(message_fakka), 0,
                          (struct sockaddr *)&receiverSocket,
                          sizeof(struct sockaddr_in))) < 0)
            perror("Send failed\n");
          cout << "Current Sent: " << strlen(message_fakka) << endl;
          printf("Current Sent Total = %d.\n", current_length);

          memset(little_buffer, 0, sizeof(little_buffer));
          if ((r = recvfrom(sc->s, little_buffer, 2000, 0,
                            (struct sockaddr *)&tempSocketAddress,
                            &tempAddrlen)) < 0)
            perror("Receive Failed");
          cout << "received length before unmarshalling: " << little_buffer
               << endl;

          // unmarshal the reply
          Message reply_received_length(
              reinterpret_cast<char *>(little_buffer));

          string msg_received_length =
              reply_received_length.getUnmarshalledMessage();

          cout << "msg_received_length " << msg_received_length << endl;
          // Change to long
          long received_length = stol(msg_received_length);
          cout << "received_length " << received_length << endl;

          if (received_length != current_length) {
            perror("Dropped packets! received_length != current_length.");
            current_length_before_marshalling -= fakka; // Drop Tolerance
          }

          printf("Current Received Total %d.\n", current_length);
        }
      }
      printf("%s", "Message Sent. ");
      printf("Current %d.\n", current_length);

    } else
      cout << "could'nt open file" << endl;
  }

  void getUsers() {

    char *msg_char = new char[1];
    msg_char[0] = ' ';
    Message view_request(Request, msg_char, strlen(msg_char), 1100, requestID++,
                         0, 0, 0);

    // char * marshalled_message = view_request.marshal();

    char marshalled_message[BUFFER_SIZE];

    string x = view_request.marshal();
    int n = x.length();
    strncpy(marshalled_message, x.c_str(), n + 1);

    int r = 1;

    if ((n = sendto(sc->s, marshalled_message,
                    strlen((const char *)marshalled_message), 0,
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

    cout << little_buffer << endl;
    while (little_buffer[cc] != 0) {
      temp.append(1, little_buffer[cc]);
      cc++;
    }

    this->users = retmap(temp);
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
