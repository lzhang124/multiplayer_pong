//
//  client.h
//  Multiplayer Pong
//
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void start_client(char *server_name[], int port_number);

#endif /* client_h */
