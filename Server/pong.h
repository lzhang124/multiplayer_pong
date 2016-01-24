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

typedef enum
{
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT,
    UP_RIGHT
} BallDir;

typedef struct
{
    int x;
    int y;
    BallDir direction;
} Ball;

#pragma pack(1)
typedef enum
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} PaddleType;

typedef struct
{
    int x;
    int y;
    PaddleType type;
} Paddle;
#pragma pack(0)

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
