#include "UDPSocketClient.h"
//#include "UDPSocketServer.h"
#include "Message.h"
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
  vector<pair<int, pair<string, string>>> requests_buffer; // user, image

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

    inet_ntop(AF_INET, &(tempSocketAddress.sin_addr), sender_ip,
              INET_ADDRSTRLEN);

    sender_port = htons((&tempSocketAddress)->sin_port);

    Message requestMsg(reinterpret_cast<char *>(Serverbuffer));
    int op_id = requestMsg.getOperation();
    //    int rpcid = requestMsg.getRPCId();
    //    size_t msgsize = requestMsg.getMessageSize();
    string msg = requestMsg.getUnmarshalledMessage();

    switch (op_id) {

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
      requests_buffer.push_back(
          make_pair(2002, make_pair(username, imageName)));

      // View Request reply
      memset(Serverlittle_buffer, 0, sizeof(Serverlittle_buffer));
      Serverlittle_buffer[0] = '1';
      Serverlittle_buffer[1] = 0;
      if (sendto(sv->s, Serverlittle_buffer,
                 strlen((const char *)Serverlittle_buffer), 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("View Request reply sendto failed");
      }

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

      this->sendReply(reinterpret_cast<char *>(
          this->Serverbuffer)); // This does nothing, why no reply like above

    } break; // end of view

    case 2004: {
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

      current_received += r;
      unsigned char little_buffer[20000];

      memset(little_buffer, 0, sizeof(little_buffer));
      sprintf((char *)(little_buffer), "%lu", current_received);

      if (sendto(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                 (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
        perror("first image frag reply send to failed");
      }

      printf("%s.\n", "Start of image receive");
      std::ofstream os(
          "/home/hkandil/Downloads/distributed_pro-master/new.jpeg");

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

          current_received += r;
          cout << "Received total " << current_received << " encoded bytes.\n";

          Message imageFrag(reinterpret_cast<char *>(little_buffer));

          string imfrag = imageFrag.getUnmarshalledMessage();
          int imfraglen = imageFrag.getMessageSize();
          MF = imageFrag.getMoreFrag();
          fragc = imageFrag.getFragCount();

          // string newY(imfrag,imfraglen);

          if (r > 0) {
            os << imfrag;
          }
          memset(little_buffer, 0, sizeof(little_buffer));
          sprintf((char *)(little_buffer), "%lu", current_received);

          if (sendto(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                     (struct sockaddr *)&tempSocketAddress, tempAddrlen) < 0) {
            perror("sendto failed");
          }
        }
      }
      os.close();

      string extract_command,
          defaultPath =
              "/home/hkandil/Downloads/distributed_pro-master/new.jpeg";
      extract_command = "steghide extract -sf " + defaultPath + " -p hk ";

      QProcess::execute(QString::fromStdString(extract_command));

      //         int n = extract_command.length();
      //         char char_array[n+1];
      //         strcpy(char_array, extract_command.c_str());
      //         system(char_array);
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

  int upload(string pathname, string imagename, string defaultimage) {
    if (pathname == "" || imagename == "" || defaultimage == "")
      return 6;
    bool nospecial = true;

    if (!nospecial) { // special chars
      return 3;       // error code for special chars as they are delimiters
    } else {

      string msg = this->username + "*" + pathname + "/" + imagename;
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

        QProcess::execute(QString::fromStdString("cp " + pathname + "/" +
                                                 defaultimage + " " + pathname +
                                                 "/s" + imagename));

        QProcess::execute(QString::fromStdString(
            "steghide embed -cf " + pathname + "/s" + imagename + " -ef " +
            pathname + "/" + imagename + " -p hk "));

        return 1;

      } else
        return 0;
    }
  }

  void request_image(string selectedUser, string selectedImage,
                     string path_full) {

    // map<string, vector<string>> users;
    // users = this->getUsers();
    vector<string> images;
    images = this->users[selectedUser];
    struct sockaddr_in ownerSocket;

    string temp_ip = images[1];
    int remote_peer_port = std::stoi(images[2], nullptr, 0); // Refaay
    cout << "Remote IP " << temp_ip << ", port " << remote_peer_port << endl;
    char remote_peer_address[1024];
    strcpy(remote_peer_address, temp_ip.c_str());

    makeDestSA(&ownerSocket, remote_peer_address, remote_peer_port);

    string image_with_full_path = path_full + "/" + selectedImage;
    string msg = this->username + "*" + image_with_full_path + "*";
    char *msg_char = new char[msg.length() + 1];
    strcpy(msg_char, msg.c_str());

    Message image_request(Request, msg_char, strlen(msg_char), 2002,
                          requestID++, 0, 0, 0);
    //  char * marshalled_message = image_request.marshal();

    char marshalled_message[BUFFER_SIZE];

    string x = image_request.marshal();
    int n = x.length();
    strncpy(marshalled_message, x.c_str(), n + 1);

    int r = 1;

    if ((n = sendto(sc->s, marshalled_message,
                    strlen((const char *)marshalled_message), 0,
                    (struct sockaddr *)&ownerSocket,
                    sizeof(struct sockaddr_in))) < 0)
      perror("Send failed\n");
  }

  void approve_image(string selectedUser, string selectedImage) {

    // map<string, vector<string>> users;
    // map containing the table of users (username, images names,
    // socket addresses)
    // users = this->getUsers(); // retreiving the map from the dos
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

  void send_image(string selectedUser, string selectedImage) {

    // map<string, vector<string>>
    //   users; // map containing the table of users (username, images names,
    // socket addresses)
    // users = this->getUsers(); // retreiving the map from the dos
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

    printf("%s.\n", "Start of Send image");
    cout << "Image Path " << selectedImage << endl;
    std::ifstream is(selectedImage, std::ifstream::binary);

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

      unsigned char little_buffer[10];
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
          if ((n = sendto(sc->s, message, strlen(message), 0,
                          (struct sockaddr *)&receiverSocket,
                          sizeof(struct sockaddr_in))) < 0)
            perror("Send failed\n");
          cout << "Current Sent: " << strlen(message) << endl;
          printf("Current Sent Total = %d.\n", current_length);

          memset(little_buffer, 0, sizeof(little_buffer));
          if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                            (struct sockaddr *)&tempSocketAddress,
                            &tempAddrlen)) < 0)
            perror("Receive Failed");
          // Change to unsigned long
          unsigned long received_length = 0;
          for (int i = 0; i < 10 && little_buffer[i] != '\0'; i++) {
            received_length *= 10;
            received_length += little_buffer[i] - '0';
          }
          cout << "received_length " << received_length << endl;

          if (received_length != current_length) {
            perror("Dropped packets! received_length != current_length.");
            current_length = received_length; // Drop Tolerance
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
          if ((r = recvfrom(sc->s, little_buffer, 10, 0,
                            (struct sockaddr *)&tempSocketAddress,
                            &tempAddrlen)) < 0)
            perror("Receive Failed");
          // Change to unsigned long
          unsigned long received_length = 0;
          for (int i = 0; i < 10 && little_buffer[i] != '\0'; i++) {
            received_length *= 10;
            received_length += little_buffer[i] - '0';
          }
          cout << "received_length " << received_length << endl;

          if (received_length != current_length) {
            perror("Dropped packets! received_length != current_length.");
            current_length = received_length; // Drop Tolerance
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
