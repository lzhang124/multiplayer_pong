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
    *ball = (Ball) {400, 400};
    return ball;
}

void update_ball(Ball * ball)
{
    if (ball->direction == DOWN_RIGHT)
    {
        if (ball->x < WINDOW_W - MARGIN)
        {
            
        }
        else if (ball->y < WINDOW_H - MARGIN)
        {
            
        }
        else
        {
            ball->x += BALL_MOVEMENT;
            ball->y += BALL_MOVEMENT;
        }
    }
    else if (ball->direction == DOWN_LEFT)
    {
        
    }
    else if (ball->direction == UP_LEFT)
    {
        
    }
    else if (ball->direction == UP_RIGHT)
    {
        
    }
}