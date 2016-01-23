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

enum ball_dir
{
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT,
    UP_RIGHT
};

typedef struct
{
    int x;
    int y;
    enum ball_dir direction;
} Ball;

enum paddle_type
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

typedef struct
{
    int x;
    int y;
    enum paddle_type type;
} Paddle;

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

Game *init_game();
void add_player(Game *game, int player_socket);
void remove_player(Game *game, int sd);
void end_game(Game *game);
void pong(int port_num);

#endif /* pong_h */
