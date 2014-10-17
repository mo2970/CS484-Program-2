#include <stdio.h>
#include <iostream>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define PORT 2970

using namespace std;

volatile sig_atomic_t clientRunFlag = 1;

// for gobal interupt of CTRL + C or X out of terminal
void exitSig(int sig){ 
  clientRunFlag = 0; 
}

int main (int argInt, char* argchar[])
{
    char userName[] = {'m','o','2','9','7','0'};
    sockaddr_in myAddr;
    int socketID = socket(AF_INET,SOCK_STREAM,0);
    
    if(socketID < 0){
        cerr << "Client initialization failed" << endl;
        return 0;
    }
    
    // for CTRL + c
    signal(SIGINT, exitSig);
    // for X out of terminal
    signal(SIGHUP, exitSig);
    
    myAddr.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&myAddr.sin_addr);
    myAddr.sin_port = htons(PORT);

    connect(socketID,(sockaddr *)&myAddr, sizeof(myAddr));

    //Send username
    int result = send(socketID,userName, strlen(userName), 0);
    if(result < 0)
	cout<<"Send failed :("<<endl;

    char buff[256];
    result = recv(socketID,buff,256,0);
	
    int userCount = 1;
    cout<<"Users online:"<<endl<<" 1:";
    for(int i=2;i<result-1;i++)
    {
    	if(buff[i] == ';')
    	{
    		userCount++;
		cout<<endl<<" "<<userCount<<":";
	}
	else
		cout<<buff[i];
    }
    cout<<endl;

	
    cin>>userCount;
    send(socketID,"C:0",3,0);
	
    int flags = fcntl(socketID, F_GETFL, 0);
    fcntl(socketID, F_SETFL, flags | O_NONBLOCK);

    //chat loop
    while(clientRunFlag)
    {
	cin.getline(buff,256);
	if(buff[0] =='S')
		send(socketID,buff,256,0);

	//needs to be a thread
	result = recv(socketID,buff,256,0);
	if(result > 0)
	{
		for(int i=0;i<254;i++)
			buff[i] = buff[i+2];
		cout<<buff<<endl;
	}
    }
    close(socketID);   
    return 0;
}
