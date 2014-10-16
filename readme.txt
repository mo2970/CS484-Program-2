Here is how I get them going. It just runs and eco from the client to the server as is.

Server
g++ Server.cpp -lpthread -o Server
./Server <port number>

Client
g++ Client.cpp -o Client
./Client localhost <port number>


