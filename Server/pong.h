//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#include <stdio.h>

#define MAX_PLAYERS 4

enum paddle_type
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

typedef struct
{
    int speed;
    double direction;
    double xCoord;
    double yCoord;
} Ball;

typedef struct
{
    enum paddle_type paddle_type;
    double x_coord;
    double y_coord;
} Paddle;

typedef struct
{
    int player_number;
    int score;
    Paddle *paddle;
} Player;

typedef struct game
{
    int number_players;
    Player *players[MAX_PLAYERS];
    Ball *ball;
    
    // may not need these
    int max_score;
    int max_player;
} Game;

Game *init_game();
void add_player(Game *game, int player_socket);
void remove_player(Game *game, int sd);
void end_game(Game *game);
void notify_players_number(int message, int from_player_number);
void notify_players_string(char *message, int from_player_number);
void pong(int port_num);

#endif /* pong_h */
