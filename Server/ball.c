//
//  ball.c
//  Multiplayer Pong
//
//

#include "ball.h"
#include "constants.h"

Ball * new_ball()
{
    Ball *ball = malloc(sizeof(*ball));
    srand((unsigned int) time(NULL));
    int x = 550 + 5 * (rand() % 88 - 44);
    int y = 350 + 5 * (rand() % 56 - 28);
    int dir = rand() % 4;
    *ball = (Ball) {x, y, dir};
    return ball;
}

void reset_ball(Ball *ball)
{
    srand((unsigned int) time(NULL));
    int x = 550 + 5 * (rand() % 88 - 44);
    int y = 350 + 5 * (rand() % 56 - 28);
    int dir = rand() % 4;
    *ball = (Ball) {x, y, dir};
}

