//
//  main.cpp
//  Directory Service
//
//  Created by Nour Ghaly  on 11/7/18.
//  Copyright © 2018 AUC. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct data {
  vector<string> img;
  bool online = false;
  string currentIP = "";
  string port = "";
};
map<string, string> auth_map;
map<string, data> users_map;

void read_first_time_users(
    fstream &users) { // load data from users file into the users map (done once
                      // when the server is opened only)
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

bool sign_up(string username, string password, fstream &auth, fstream &users) {
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

bool login(string username, string password, string current_ip, string port_num,
           fstream &auth) {
  // checks of the username and password are correct, if so -> update the
  // user_map of this user
  bool flag = false;
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
      if (name == username && pass == password) {
        flag = true;
        break;
      }
    }
  }
  auth.clear();
  if (!flag)
    return false;
  users_map[username].online = true;
  users_map[username].currentIP = current_ip;
  users_map[username].port = port_num;
  return true;
}

void logout(string username) {
  users_map[username].online = false;
  users_map[username].currentIP = "";
  users_map[username].port = "";
}

void view() {
  cout << "USERNAME:   Images:" << endl;
  for (auto const &x : users_map) {
    cout << x.first << " ";
    for (int i = 0; i < x.second.img.size(); i++) {
      cout << x.second.img[i] << " ";
    }
    cout << endl;
  }
  cout << "************" << endl;
}

int main() { // int argc, const char * argv[]
  fstream auth, users;
  auth.open("auth.txt", fstream::out | fstream::in | fstream::app);
  if (auth.fail())
    cout << "fail";
  /*else
    cout << "ok" << endl;*/

  users.open("users.txt", fstream::out | fstream::in | fstream::app);
  if (users.fail())
    cout << "fail";

  read_first_time_auth(auth);
  read_first_time_users(users);
  /*if (users_map.count("Hassan") > 0)
    cout << users_map["Hassan"].img[0] << users_map["Hassan"].img[1] << endl;*/
  sign_up("Hassan", "hassona", auth, users);
  if (auth_map.count("Hassan") > 0)
    cout << auth_map["Hassan"] << endl; // password

  login("Hassan", "hassona", "192.168.10.20", "8080", auth);
  if (users_map.count("Hassan") > 0)
    cout << users_map["Hassan"].online << " " << users_map["Hassan"].currentIP
         << " " << users_map["Hassan"].port << endl;

  /*cout << users_map["Lotfy"].img[0] << users_map["Lotfy"].img[1] << endl;

  // sign_up("Yasser", "No5", auth, users);
  // cout<<auth_map["Yasser"];
  cout << login("Yasser", "No5", "1000", "8080", auth) << endl;
  // cout<<login("Yasser", "No", "1000", "8080", auth)<<endl;

  cout << users_map["Yasser"].online << " " << users_map["Yasser"].port <<
  endl; logout("Yasser"); cout << users_map["Yasser"].online << " " <<
  users_map["Yasser"].port << endl; view();*/
  return 0;
}
