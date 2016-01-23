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

int start_server(int port_num);
int add_connection(int master_socket, int client_sockets[], int max_connections);
long handle_connection(fd_set *readfds, int client_sockets[], int max_connections, int *sd, char buffer[]);
int wait_for_connection(int master_socket, int max_connections, fd_set *readfds, int client_sockets[]);

void error(const char *msg);

#endif /* server_h */
