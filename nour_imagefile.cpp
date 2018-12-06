//
//  main.cpp
//  newdos
//
//  Created by Nour Ghaly  on 11/30/18.
//  Copyright © 2018 AUC. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct image {
  int viewsnum = 0;
  string ownername;
};
map<string, image> sharedimgs;

bool newimg(string img, string owner, int views) {
  // insert a new image in the map
  bool flag = true; // if there is a duplicate of the image name and owner name,
                    // change the flag to false.
  for (auto const &x : sharedimgs) {
    cout << (x.first == img) << "" << (x.second.ownername == owner) << endl;
    if (x.first == img && x.second.ownername == owner) {
      return false;
    }
  }

  sharedimgs[img].viewsnum = views;
  sharedimgs[img].ownername = owner;
  return true;
}
void updatefile(fstream &imgfile) {
  // call this function when the user is signing out, to update the file
  imgfile.close();
  imgfile.open("imagefile.txt", fstream::out | fstream::in);

  for (auto const &x : sharedimgs) {
    imgfile << x.first << " " << x.second.ownername << " " << x.second.viewsnum
            << endl;
  }
}
void readfile(fstream &imgfile) {
  // call this function once, when the user logs in to fill in the map from what
  // is in the file
  imgfile.seekp(0);
  while (!imgfile.eof()) {
    string line;
    getline(imgfile, line);
    if (line != "") {
      int name_len, owner_len, view_len;
      name_len = line.find(" ");
      string img = line.substr(0, name_len);
      line = line.erase(0, name_len + 1);
      owner_len = line.find(" ");
      string owner = line.substr(0, owner_len);
      line = line.erase(0, owner_len + 1);
      view_len = line.find(" ");
      string views = line.substr(0, view_len);
      line = line.erase(0, view_len + 1);
      sharedimgs[img].ownername = owner;
      int view = stoi(views);
      sharedimgs[img].viewsnum = view;
    }
  }
  imgfile.clear();
}
int main(int argc, const char *argv[]) {
  fstream auth, users, imgfile;
  imgfile.open("imagefile.txt", fstream::out | fstream::in | fstream::app);
  if (imgfile.fail())
    cout << "fail";
  else
    cout << "ok" << endl;
  readfile(imgfile);
  cout << newimg("x.jpg", "nour", 6) << endl;
  cout << newimg("y.jpg", "ahmed", 4) << endl;
  updatefile(imgfile);
}
