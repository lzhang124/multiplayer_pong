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

#include "message.h"

int start_server(int port_num);
int wait_for_connection(int master_socket);
int add_connection(int master_socket);
int check_socket();
void disconnect(int client_number);
void end_connection(int master_socket);

void notify_others(int client_number, Message *msg);
void notify_all(Message *msg);
void send_message(int client_number, Message *msg);
void read_message(int client_number, Message *msg);

#endif /* server_h */
