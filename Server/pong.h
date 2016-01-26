//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#include <stdio.h>
#include <stdlib.h>
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
    int max_score;
} Game;

void pong(int port_num);

#endif /* pong_h */
