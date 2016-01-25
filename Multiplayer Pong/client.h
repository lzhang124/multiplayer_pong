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
#include <fcntl.h>

#include "message.h"

int start_client(char *server_name[], int port_num);
void write_message(int master_socket, Message *msg);
void read_message(int master_socket, Message *msg);
void end_connection(int master_socket);

#endif /* client_h */
