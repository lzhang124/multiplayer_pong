//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#include <stdio.h>

struct ball
{
    int speed;
    double direction;
    double xCoord;
    double yCoord;
};

struct paddle
{
    double xCoord;
    double yCoord;
};

struct player
{
    int player_socket;
    int score;
    struct paddle *paddle;
};

// calculates new paddle coordinates
void moveLeft(struct player* player, struct paddle *paddle);

void moveRight(struct player* player, struct paddle *paddle);

// calculates the location of the ball
void calculateBallLocation(struct ball *ball);




#endif /* pong_h */
