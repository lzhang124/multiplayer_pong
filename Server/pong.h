//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "message.h"
#include "ball.h"
#include "paddle.h"

typedef struct
{
    int number_players;
    Paddle *paddles[MAX_PLAYERS];
    Ball *ball;
    int started;
} Game;

void pong(int port_num);

#endif /* pong_h */
