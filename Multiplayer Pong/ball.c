//
//  ball.c
//  Multiplayer Pong
//
//  Created by Larry Zhang on 1/22/16.
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

void update_ball(Ball * ball)
{
    if (ball->direction == DOWN_RIGHT)
    {
        ball->x += BALL_MOVEMENT;
        ball->y += BALL_MOVEMENT;
        if (ball->x == WINDOW_W - MARGIN - BALL_W)
        {
            ball->direction = DOWN_LEFT;
        }
        else if (ball->y == WINDOW_H - MARGIN - BALL_H)
        {
            ball->direction = UP_RIGHT;
        }
        else if (ball->x == WINDOW_W - MARGIN - BALL_W && ball->y == WINDOW_H - MARGIN - BALL_H)
        {
            ball->direction = UP_LEFT;
        }
    }
    else if (ball->direction == DOWN_LEFT)
    {
        ball->x -= BALL_MOVEMENT;
        ball->y += BALL_MOVEMENT;
        if (ball->x == MARGIN)
        {
            ball->direction = DOWN_RIGHT;
        }
        else if (ball->y == WINDOW_H - MARGIN - BALL_H)
        {
            ball->direction = UP_LEFT;
        }
        else if (ball->x == WINDOW_W - MARGIN - BALL_W && ball->y == WINDOW_H - MARGIN - BALL_H)
        {
            ball->direction = UP_RIGHT;
        }
    }
    else if (ball->direction == UP_LEFT)
    {
        ball->x -= BALL_MOVEMENT;
        ball->y -= BALL_MOVEMENT;
        if (ball->x == MARGIN)
        {
            ball->direction = UP_RIGHT;
        }
        else if (ball->y == MARGIN)
        {
            ball->direction = DOWN_LEFT;
        }
        else if (ball->x == MARGIN && ball->y == MARGIN)
        {
            ball->direction = DOWN_RIGHT;
        }
    }
    else if (ball->direction == UP_RIGHT)
    {
        ball->x += BALL_MOVEMENT;
        ball->y -= BALL_MOVEMENT;
        if (ball->x == WINDOW_W - MARGIN - BALL_W)
        {
            ball->direction = UP_LEFT;
        }
        else if (ball->y == MARGIN)
        {
            ball->direction = DOWN_RIGHT;
        }
        else if (ball->x == WINDOW_W - MARGIN - BALL_W && ball->y == MARGIN)
        {
            ball->direction = DOWN_LEFT;
        }
    }
}
