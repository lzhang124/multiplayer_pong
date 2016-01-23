//
//  paddle.c
//  Multiplayer Pong
//
//  Created by Larry Zhang on 1/22/16.
//
//

#include "paddle.h"
#include "constants.h"

Paddle * add_paddle(int paddle_number)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    if (paddle_number == LEFT)
    {
        *paddle = (Paddle) {10, 355, LEFT};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {820, 355, RIGHT};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {355, 10, TOP};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {355, 820, BOTTOM};
    }
    return paddle;
}

void move_up(Paddle * paddle)
{
    if (paddle->loc == LEFT || paddle->loc == RIGHT)
    {
        if (paddle->y >= MARGIN + PADDLE_MOVEMENT)
        {
            paddle->y -= PADDLE_MOVEMENT;
        }
    }
}

void move_down(Paddle * paddle)
{
    if (paddle->loc == LEFT || paddle->loc == RIGHT)
    {
        if (paddle->y <= WINDOW_H - PADDLE_H - MARGIN - PADDLE_MOVEMENT)
        {
            paddle->y += PADDLE_MOVEMENT;
        }
    }
}

void move_left(Paddle * paddle)
{
    if (paddle->loc == TOP || paddle->loc == BOTTOM)
    {
        if (paddle->x >= MARGIN + PADDLE_MOVEMENT)
        {
            paddle->x -= PADDLE_MOVEMENT;
        }
    }
}

void move_right(Paddle * paddle)
{
    if (paddle->loc == TOP || paddle->loc == BOTTOM)
    {
        if (paddle->x <= WINDOW_W - PADDLE_H - MARGIN - PADDLE_MOVEMENT)
        {
            paddle->x += PADDLE_MOVEMENT;
        }
    }
}
