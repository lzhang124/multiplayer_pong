//
//  main.c
//  Multiplayer Pong
//
//

#include "pong.h"

#define SERVER_PORT 9000

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage %s hostname\n", argv[0]);
        exit(0);
    }
    
    // second argument is the server name
    pong(argc, argv, &argv[1], SERVER_PORT);
    return 0;
}