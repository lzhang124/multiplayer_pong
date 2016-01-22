//
//  server.h
//  Multiplayer Pong
//
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define MAX_PLAYERS 10

struct socket_manager
{
    int serverSocket;
    int serverPort;
    int numberConnections;
    int players[MAX_PLAYERS];
};

void server();

void closeSocket(int socket, struct socket_manager *manager);

#endif /* server_h */
