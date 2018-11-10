//
//  main.cpp
//  Directory Service
//
//  Created by Nour Ghaly  on 11/7/18.
//  Copyright © 2018 AUC. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct data{
    vector<string> img;
    bool online=false;
    string currentIP="";
    string port="";
};
map<string, string> auth_map;
map<string, data> users_map;

void read_first_time_users(fstream & users){ //load data from users file into the users map (done once when the server is opened only)
    users.seekp(0);
    while(!users.eof()){
        string line;
        getline (users, line);
        if(line!=""){
            int name_len;
            name_len= line.find(" ");
            string name = line.substr(0,name_len);
            line= line.erase(0, name_len+1);
            users_map[name];
            while (line!=""){
                int image_len= line.find(" ");
                string image = line.substr(0,image_len);
                line= line.erase(0, image_len+1);
                users_map[name].img.push_back(image);
            }
        }
    }
    users.clear();
}
void read_first_time_auth(fstream & auth){//load data from auth file into the auth map (done once when the server is opened only)
    auth.seekp(0);
    while (!auth.eof()) {
        string line;
        getline(auth, line);
        if(line!=""){
            int name_len;
            name_len= line.find(" ");
            string name = line.substr(0,name_len);
            line= line.erase(0, name_len+1);
            int pass_len= line.find(" ");
            string pass = line.substr(0,pass_len);
            line= line.erase(0, pass_len+1);
            auth_map[name]=pass;
        }
    }
    auth.clear();
}
void read_first_time(fstream & auth, fstream & users ){//load both files
    read_first_time_auth(auth);
    read_first_time_users(users);
}

void sign_up(string username, string password,fstream & auth, fstream & users ){
    bool flag=false;
    auth.seekp(0);
    while(!auth.eof()){
        string line;
        getline(auth, line);
        if(line!=""){
            int name_len;
            name_len= line.find(" ");
            string name = line.substr(0,name_len);
            if (name==username) flag=true;
        }
        
    }
    auth.clear();
    if(!flag){
    auth_map[username]=password;
    users_map[username];
    int ind= auth.tellg();
    auth.seekp(ind);
    auth<<username<<" "<<password<<endl;
    int inds= users.tellg();
    users.seekp(inds);
    users<<username<<" "<<endl;
    }
    else cout<<"Username already exists\n";
}

bool login (string username, string password, string current_ip, string port_num, fstream & auth){
    //checks of the username and password are correct, if so -> update the user_map of this user
    bool flag=false;
    auth.seekp(0);
    while(!auth.eof()){
        string line;
        getline(auth, line);
        if(line!=""){
            int name_len;
            name_len= line.find(" ");
            string name = line.substr(0,name_len);
            line= line.erase(0, name_len+1);
            int pass_len= line.find(" ");
            string pass = line.substr(0,pass_len);
            line= line.erase(0, pass_len+1);
            if (name==username && pass==password) {flag= true; break;}
        }
        
    }
    auth.clear();
    if (!flag)
        return false;
    users_map[username].online=true;
    users_map[username].currentIP= current_ip;
    users_map[username].port= port_num;
    return true;
}

void logout (string username){
    users_map[username].online= false;
    users_map[username].currentIP="";
    users_map[username].port="";
}

void view (){
    cout<<"USERNAME:   Images:"<<endl;
    for (auto const &x:users_map){
        cout <<x.first<<" ";
        for ( int i=0; i<x.second.img.size(); i++){
            cout<<x.second.img[i]<<" ";
        }
        cout<<endl;
    }
    cout<<"************"<<endl;
}

void upload (string username, string img_name, fstream & users){ // Upload a new image to an existing user by updating the users map and file
    bool flag = false; // flag to check if that user exists in the first place
    string Final="";
    for (auto const &x:users_map){
        if (x.first== username) {flag = true; break;}
    }
    if (flag){
        users_map[username].img.push_back(img_name);
        users.seekg(0);
        while (!users.eof()) {
            string line;
            getline (users, line);
            if (line=="") break;
            string orig =line;
            int name_len;
            name_len= line.find(" ");
            string name = line.substr(0,name_len);
            line= line.erase(0, name_len+1);
            if (name==username){
                Final+=username+" ";
                for (int i=0; i<users_map[username].img.size(); i++)
                    Final+=users_map[username].img[i]+" ";
                Final+="\n";
            }
            else{
                Final+=orig+"\n";
            }
        }
    }
    else{
        cout<<"Username not found \n";
    }
    users.close();
    users.open ("users.txt", fstream::out | fstream::in);
    users<<Final;
}

void show_online(){
    cout<<"Online users\nUsername IP port\n";
    for (auto const &x:users_map){
        if (x.second.online)
        {
            cout<<x.first<<" "<<x.second.currentIP<<" "<<x.second.port<<endl;
        }
    }
    cout<<"**************\n";

}


int main(int argc, const char * argv[]) {
    fstream auth, users;
    auth.open ("auth.txt", fstream::out | fstream::in | fstream::app );
    if (auth.fail())
        cout<<"fail";
    else
        cout<<"ok"<<endl;

    users.open ("users.txt", fstream::out | fstream::in | fstream::app );
    if (users.fail())
        cout<<"fail";
    else
        cout<<"ok"<<endl;
    
    read_first_time_auth(auth);
    read_first_time_users(users);
    cout<<users_map["Hassan"].img[0]<<users_map["Hassan"].img[1]<<endl;
    cout<<users_map["Lotfy"].img[0]<<users_map["Lotfy"].img[1]<<endl;
    
//    sign_up("Yasser", "No5", auth, users);
//    upload("Yasser", "hello.jpg", users);
//    upload("Yasser", "hi.jpg", users);
//    upload("Hassan", "new.jpg", users);
//    cout<<auth_map["Yasser"];
    cout<<login("Yasser", "No5", "1000", "8080", auth)<<endl;
//    cout<<login("Yasser", "No", "1000", "8080", auth)<<endl;

    cout<<users_map["Yasser"].online<<" "<<users_map["Yasser"].port<<endl;
    show_online();
    //logout("Yasser");
    //cout<<users_map["Yasser"].online<<" "<<users_map["Yasser"].port<<endl;
    //view();
    return 0;
}
