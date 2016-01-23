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
int wait_for_connection(int master_socket);
int add_connection(int master_socket);
int check_socket();
void disconnect(int client_number);
void end_connection(int master_socket);

void send_string(int client_number, char *buffer);
char *read_string(int client_number);
void send_number(int client_number, int number);
int read_number(int client_number);

#endif /* server_h */
