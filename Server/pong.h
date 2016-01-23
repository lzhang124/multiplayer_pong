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
    double x_coord;
    double y_coord;
} Paddle;

typedef struct
{
    int player_socket;
    int score;
    enum paddle_type paddle_type;
    Paddle *paddle;
} Player;

typedef struct game
{
    int server_socket;
    int server_port;
    int number_players;
    Player *players;
    Ball *ball;
    
    // may not need these
    int max_score;
    int max_player;
} Game;

void pong(int port_num);
Game *init_game(int server_socket, int server_port);
void wait_for_players(Game *game);
void add_player(Game *game, int player_socket);
void disconnect_player(Game *game, int sd);



#endif /* pong_h */
