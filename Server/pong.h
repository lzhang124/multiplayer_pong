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
    int player_number;
    int score;
    Paddle *paddle;
} Player;

typedef struct
{
    int number_players;
    Player *players[MAX_PLAYERS];
    Ball *ball;
} Game;

void pong(int port_num);

#endif /* pong_h */
