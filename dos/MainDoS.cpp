
#include "DoS.h"
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

int main() {

  DoS dos;
  while (1) {
    dos.serveRequests();
  }

  return 0;
}
