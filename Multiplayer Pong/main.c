//
//  main.c
//  Multiplayer Pong
//
//

#include "client.h"
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
    start_client(&argv[1], SERVER_PORT);
    
    pong(argc, argv);
    return 0;
}
