//
//  server.c
//  Multiplayer Pong
//
//

#include "pong.h"

#define SERVER_PORT 9000

int main(int argc, char *argv[])
{
    pong(SERVER_PORT);
    return 0;
}