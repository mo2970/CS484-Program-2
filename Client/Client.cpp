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

int main (int argInt, char* argchar[])
{
    int socketNumber = socket(AF_INET, SOCK_STREAM, 0);
    int portNumber = atoi(argchar[2]);
    
    struct sockaddr_in svrAddress;
    struct hostent *serverHost = gethostbyname(argchar[1]);

    
    if(argInt < 2 || socketNumber < 0 || serverHost == NULL){
        cerr << "Client initialization failed" << endl;
        return 0;
    }

    
    bzero((char *) &svrAddress, sizeof(svrAddress));
    svrAddress.sin_family = AF_INET;
    
    bcopy((char *) serverHost -> h_addr, (char *) &svrAddress.sin_addr.s_addr, serverHost -> h_length);
    
    svrAddress.sin_port = htons(portNumber);
    
    
    // for CTRL + c
    signal(SIGINT, exitSig);
    // for X out of terminal
    signal(SIGHUP, exitSig);
    
    while(clientRunFlag)
    {
        
    }
   
    return 0;
}
