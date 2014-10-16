#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <signal.h>

using namespace std;

volatile sig_atomic_t clientRunFlag = 1;

// for gobal interupt of CTRL + C or X out of terminal
void exitSig(int sig){ 
  clientRunFlag = 0; 
}

int main (int argc, char* argv[])
{
    
    // for CTRL + c
    signal(SIGINT, exitSig);
    // for X out of terminal
    signal(SIGHUP, exitSig);
    
    
    while(clientRunFlag)
    {
        
    }
    
    
    return 0;
}
