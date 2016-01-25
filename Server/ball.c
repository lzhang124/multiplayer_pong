//
//  ball.c
//  Multiplayer Pong
//
//

#include "ball.h"
#include "constants.h"

Ball * add_ball()
{
    Ball *ball = malloc(sizeof(*ball));
    srand((unsigned int) time(NULL));
    int x = 255 + 5 * (rand() % 80);
    int y = 255 + 5 * (rand() % 80);
    int dir = rand() % 4;
    *ball = (Ball) {x, y, dir};
    return ball;
}
