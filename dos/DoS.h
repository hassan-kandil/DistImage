#ifndef DOS_H
#define DOS_H
#define BUFFER_SIZE 3000000
#define LITTLE_BUFFER_SIZE 20000

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "UDPSocketServer.h"
#include "base64.h"
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

struct data {
  vector<string> img;
  bool online = false;
  string currentIP = "";
  string port = "";
};

class DoS {
private:
  UDPSocketServer *sv;
  fstream auth, users;
  map<string, string> auth_map;
  map<string, data> users_map;
  bool con;
  int port;
  char sender_ip[INET_ADDRSTRLEN];
  uint16_t sender_port;

public:
  int r;

  struct sockaddr_in recievedAddr;

  socklen_t addresslength = sizeof(recievedAddr);

  unsigned char buffer[BUFFER_SIZE];
  unsigned char little_buffer[LITTLE_BUFFER_SIZE];

  DoS() {
    cout << "Enter the port: ";
    cin >> port;

    con = true;
    sv = new UDPSocketServer(port);
    auth.open("auth.txt", fstream::out | fstream::in | fstream::app);
    if (auth.fail())
      cout << "Auth file open failed!";

    users.open("users.txt", fstream::out | fstream::in | fstream::app);
    if (users.fail())
      cout << "Users file open failed!";

    read_first_time_auth(auth);
    read_first_time_users(users);
  }

  void getRequest() {
    printf("%s.\n", "Start of getRequest");
    unsigned long current_received = 0;

    memset(buffer, 0, sizeof(buffer));
    // Receive Marshalled Message
    r = recvfrom(sv->s, buffer, BUFFER_SIZE, 0,
                 (struct sockaddr *)&recievedAddr, &addresslength);

    printf("Received Message = %s.\n", buffer);

    inet_ntop(AF_INET, &(recievedAddr.sin_addr), sender_ip, INET_ADDRSTRLEN);

    sender_port = htons((&recievedAddr)->sin_port);

    printf("Sign up IP:%s & port: %d\n", sender_ip, sender_port);

    // Get operation ID as unsigned long
    unsigned long op_id = 0;
    for (int i = 0; i < 4 && buffer[i] != '\0'; i++) {
      op_id *= 10;
      op_id += buffer[i] - '0';
      // cout << op_id << endl;
    }

    printf("Received op_id = %lu.\n", op_id);
    switch (op_id) {
    case 1001: // sign_up
    {
      int cc = 4;
      string username = "", password = "";
      while (buffer[cc] != '*') {
        username.append(1, buffer[cc]);
        cc++;
      }
      cc++;
      while (buffer[cc] != 0) {
        password.append(1, buffer[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Pass: " << password << endl;
      bool didsign = sign_up(username, password);
      cout << "Signed up?" << didsign << endl;
      // Sign Up reply
      memset(little_buffer, 0, sizeof(little_buffer));
      if (didsign)
        little_buffer[0] = '1';
      else
        little_buffer[0] = '0';
      // sprintf((char *)(little_buffer), "%d", didsign);
      little_buffer[1] = 0;
      if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
                 (struct sockaddr *)&recievedAddr, addresslength) < 0) {
        perror("Sign up reply sendto failed");
      }

    } break; // end of sign_up

    case 1002: // login
    {
      int cc = 4;
      string username = "", password = "";
      while (buffer[cc] != '*') {
        username.append(1, buffer[cc]);
        cc++;
      }
      cc++;
      while (buffer[cc] != 0) {
        password.append(1, buffer[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Pass: " << password << endl;
      int didlogin = login(username, password);

      cout << "Logged in? " << didlogin << endl;
      // Sign Up reply
      memset(little_buffer, 0, sizeof(little_buffer));
      if (didlogin == 1)
        little_buffer[0] = '1';
      else if (didlogin == 0)
        little_buffer[0] = '0';
      else if (didlogin == 5)
        little_buffer[0] = '5';
      else
        little_buffer[0] = '4';
      little_buffer[1] = 0;
      if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
                 (struct sockaddr *)&recievedAddr, addresslength) < 0) {
        perror("Sign up reply sendto failed");
      }

    } break; // end of login

    case 1003: // logout
    {
      int cc = 4;
      string username = "";
      while (buffer[cc] != 0) {
        username.append(1, buffer[cc]);
        cc++;
      }

      cout << "User: " << username << endl;

      bool wasin = logout(username);

      cout << "Logged out? " << wasin << endl;

      // Sign Up reply
      memset(little_buffer, 0, sizeof(little_buffer));
      if (wasin == true)
        little_buffer[0] = '1';
      else
        little_buffer[0] = '0';
      little_buffer[1] = 0;
      if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
                 (struct sockaddr *)&recievedAddr, addresslength) < 0) {
        perror("Sign up reply sendto failed");
      }

    } break; // end of logout

    case 1100: // view
    {

      string res = view();

      cout << "View All. Text: " << res << endl;

      // Sign Up reply
      memset(little_buffer, 0, sizeof(little_buffer));

      sprintf((char *)(little_buffer), "%s", res.c_str());

      if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
                 (struct sockaddr *)&recievedAddr, addresslength) < 0) {
        perror("Sign up reply sendto failed");
      }

    } break; // end of view

    case 2001: // upload
    {
      int cc = 4;
      string username = "", imagename = "";
      while (buffer[cc] != '*') {
        username.append(1, buffer[cc]);
        cc++;
      }
      cc++;
      while (buffer[cc] != 0) {
        imagename.append(1, buffer[cc]);
        cc++;
      }
      cout << "User: " << username << endl;
      cout << "Imagename: " << imagename << endl;
      int uploaded = upload(username, imagename);

      cout << "Uploaded? " << uploaded << endl;
      // Sign Up reply
      memset(little_buffer, 0, sizeof(little_buffer));
      if (uploaded == 1)
        little_buffer[0] = '1';
      else
        little_buffer[0] = '0';
      little_buffer[1] = 0;
      if (sendto(sv->s, little_buffer, strlen((const char *)little_buffer), 0,
                 (struct sockaddr *)&recievedAddr, addresslength) < 0) {
        perror("Sign up reply sendto failed");
      }

    } break; // end of upload

    

    default:
      break;
    }
  }

  void receiveImage() {
    printf("%s.\n", "Start of getRequest");
    unsigned long current_received = 0;
    memset(buffer, 0, sizeof(buffer));
    std::ofstream os("new_2.jpeg");
    memset(little_buffer, 0, sizeof(little_buffer));
    // Receive Image Length
    r = recvfrom(sv->s, little_buffer, LITTLE_BUFFER_SIZE, 0,
                 (struct sockaddr *)&recievedAddr, &addresslength);
    printf("Received Length of Encoded Message (char[]) = %s.\n",
           little_buffer);
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

  void sendReply() {
    if (sendto(sv->s, buffer, r, 0, (struct sockaddr *)&recievedAddr,
               addresslength) < 0) {
      perror("sendto failed");
    }
  }

  bool serveRequests() { getRequest(); }

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

      char_array_3[0] =
          (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] =
          ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

      for (j = 0; (j < i - 1); j++)
        ret += char_array_3[j];
    }

    return ret;
  }

  void read_first_time_users(
      fstream &users) { // load data from users file into the users map (done
                        // once when the server is opened only)
    users.seekp(0);
    while (!users.eof()) {
      string line;
      getline(users, line);
      if (line != "") {
        int name_len;
        name_len = line.find(" ");
        string name = line.substr(0, name_len);
        line = line.erase(0, name_len + 1);
        users_map[name];
        while (line != "") {
          int image_len = line.find(" ");
          string image = line.substr(0, image_len);
          line = line.erase(0, image_len + 1);
          users_map[name].img.push_back(image);
        }
      }
    }
    users.clear();
  }
  void read_first_time_auth(
      fstream &auth) { // load data from auth file into the auth map (done once
                       // when the server is opened only)
    auth.seekp(0);
    while (!auth.eof()) {
      string line;
      getline(auth, line);
      if (line != "") {
        int name_len;
        name_len = line.find(" ");
        string name = line.substr(0, name_len);
        line = line.erase(0, name_len + 1);
        int pass_len = line.find(" ");
        string pass = line.substr(0, pass_len);
        line = line.erase(0, pass_len + 1);
        auth_map[name] = pass;
      }
    }
    auth.clear();
  }
  void read_first_time(fstream &auth, fstream &users) { // load both files
    read_first_time_auth(auth);
    read_first_time_users(users);
  }

  bool sign_up(string username, string password) {
    bool flag = false;
    auth.seekp(0);
    while (!auth.eof()) {
      string line;
      getline(auth, line);
      if (line != "") {
        int name_len;
        name_len = line.find(" ");
        string name = line.substr(0, name_len);
        if (name == username)
          flag = true;
      }
    }
    auth.clear();
    if (!flag) {
      auth_map[username] = password;
      users_map[username];
      int ind = auth.tellg();
      auth.seekp(ind);
      auth << username << " " << password << endl;
      int inds = users.tellg();
      users.seekp(inds);
      users << username << " " << endl;
      return true;
    } else
      return false; // cout << "Username already exists\n";
  }

  int login(string username, string password) {
    // checks of the username and password are correct, if so -> update the
    // user_map of this user
    bool flag = false;
    bool flag2 = false;
    auth.seekp(0);
    while (!auth.eof()) {
      string line;
      getline(auth, line);
      if (line != "") {
        int name_len;
        name_len = line.find(" ");
        string name = line.substr(0, name_len);
        line = line.erase(0, name_len + 1);
        int pass_len = line.find(" ");
        string pass = line.substr(0, pass_len);
        line = line.erase(0, pass_len + 1);
        if (name == username)
          flag = true;
        if (pass == password)
          flag2 = true;
        if (flag & flag2)
          break;
      }
    }
    auth.clear();
    if (!flag)
      return 0;
    if (!flag2)
      return 5;
    if (users_map[username].online == true) { // already in
      return 4;
    } else { // successfully in

      users_map[username].online = true;

      string current_ip, port_num;

      char little_buffer22[LITTLE_BUFFER_SIZE];
      sprintf((char *)(little_buffer22), "%u", sender_port);
      users_map[username].currentIP = string(sender_ip);
      users_map[username].port = string(little_buffer22);
      return 1;
    }
  }

  bool logout(string username) {
    bool wasin = users_map[username].online;
    users_map[username].online = false;
    users_map[username].currentIP = "";
    users_map[username].port = "";
    return wasin;
  }

  int upload(string username,
             string img_name) { // Upload a new image to an existing user by
                                // updating the users map and file
    bool flag = false; // flag to check if that user exists in the first place
    string Final = "";
    for (auto const &x : users_map) {
      if (x.first == username) {
        flag = true;
        break;
      }
    }
    if (flag) {
      users_map[username].img.push_back(img_name);
      users.seekg(0);
      while (!users.eof()) {
        string line;
        getline(users, line);
        if (line == "")
          break;
        string orig = line;
        int name_len;
        name_len = line.find(" ");
        string name = line.substr(0, name_len);
        line = line.erase(0, name_len + 1);
        if (name == username) {
          Final += username + " ";
          for (int i = 0; i < users_map[username].img.size(); i++)
            Final += users_map[username].img[i] + " ";
          Final += "\n";
        } else {
          Final += orig + "\n";
        }
      }
    } else {
      cout << "Username not found \n";
      return 0;
    }
    users.close();
    users.open("users.txt", fstream::out | fstream::in);
    users << Final;
    return 1;
  }

  string view() {

    string ret = "";

    for (auto const &x : users_map) {

      ret += x.first + "*";

      if (x.second.online) {

        ret += "1&";

        ret += x.second.currentIP + "&";

        ret += x.second.port + "&";

      }

      else {

        ret += "0&&&";
      }

      for (int i = 0; i < x.second.img.size(); i++) {

        ret += x.second.img[i] + "#";
      }

      ret += "@";
    }

    return ret;
  }

  ~DoS() {}
};
#endif
