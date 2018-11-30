/*#include <fstream>
#include <iostream>
using namespace std;

int main() {
  string steg_image_name = "q_batman.jpeg";
  cout << "Image name "
       << "batman.jpeg"
       << " Steg name " << steg_image_name << endl;
  std::ifstream is(steg_image_name, std::ifstream::binary);
  if (is) {
    cout << "ok" << endl;
  } else
    cout << "could'nt open file" << endl;
  return 0;
}*/
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working dir: %s\n", cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }
  return 0;
}
