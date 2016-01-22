//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#include <stdio.h>

struct player
{
    int socket;
    int score;
};

struct paddle
{
    double xCoord;
    double yCoord;
};

#endif /* pong_h */
