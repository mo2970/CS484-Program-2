#include <iostream>
#include <cstring>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>

#define PORT 2970

using namespace std;

bool validateUser();

struct User
{
	char name[10];
	int socketID;
	int chatPartner;
};

int main()
{
	vector<User> users;
	
	sockaddr_in myAddr;
	sockaddr &myAddrP = (sockaddr& )myAddr; //why this?!

	int socketID = socket(AF_INET,SOCK_STREAM,0);
	if(socketID == 0)
	{
		cout<<"Error Check shenanigans"<<endl;
		return 0;
	}

	bzero(&myAddr,sizeof(myAddr)); //bzero?
	
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddr.sin_port = htons(PORT);

	int result = bind(socketID,&myAddrP, sizeof(myAddr));
	if(result < 0)
		cout<<"Failed to bind"<<endl;
	listen(socketID,5);


	//set accept socket to nonblocking
	int flags = fcntl(socketID, F_GETFL, 0);
	fcntl(socketID, F_SETFL, flags | O_NONBLOCK);

	while(true)
	{
		int clientSock = 0;
		clientSock = accept(socketID, (sockaddr *) NULL, NULL);
		if(clientSock>0)
		{
			User currentUser;
			result = recv(clientSock, currentUser.name, 10, 0);
			if(result < 0)
				cout<<"recv fail :("<<endl;
			currentUser.name[result-1] = 0;		
			cout<<currentUser.name<<" CONNECTED!"<<endl;
			currentUser.chatPartner = -1;

			//recv username
			if(validateUser())
			{
				//send list of people online
				currentUser.socketID = clientSock;	
				fcntl(clientSock, F_SETFL, flags | O_NONBLOCK);
				users.push_back(currentUser);
				char msg[100];
				msg[0] = 'O';
				msg[1] = ':';
				msg[2] = 0;
				for(int i=0;i<users.size();i++)
					if(users.at(i).chatPartner == -1)
					{
						strcat(msg,users.at(i).name);
						strcat(msg,";");
					}
				send(clientSock,msg,strlen(msg),0);
			}
			else
				close(clientSock);
		}
		//update messages
		char msg[256];
		for(int i=0;i<users.size();i++)
		{
			result = recv(users.at(i).socketID, msg, 255, 0);
			if(result>0)
			{
				if(msg[0] == 'S')
				{
					//send a message to the user I am attached to.
					send(users.at(users.at(i).chatPartner).socketID,msg,255,0);
				}
				if(msg[0] == 'C')
				{
					//send a connect request to the user I specified.
					users.at(0).chatPartner = 1;
					users.at(1).chatPartner = 0;
				}
			}
		}
			
	}
	close(socketID);
	return 0;
}

bool validateUser()
{
	return true;
}