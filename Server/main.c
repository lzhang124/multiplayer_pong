//
//  server.c
//  Multiplayer Pong
//
//

#include "server.h"

#define SERVER_PORT 9000

int main(int argc, char *argv[])
{
    start_server(SERVER_PORT);
    return 0;
}
