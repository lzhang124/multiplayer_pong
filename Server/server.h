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

#include "pong.h"

#define MAX_PLAYERS 4

void start_server(int port_num);

#endif /* server_h */
