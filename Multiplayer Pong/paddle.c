//
//  paddle.c
//  Multiplayer Pong
//
//  Created by Larry Zhang on 1/22/16.
//
//

#include "paddle.h"

unsigned const int WINDOW_W = 800;
unsigned const int WINDOW_H = 800;
unsigned const int PADDLE_W = 5;
unsigned const int PADDLE_H = 100;
unsigned const int DEFAULT_MOVEMENT = 20;

Paddle * set_paddle(int paddle_number)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    if (paddle_number == LEFT)
    {
        *paddle = (Paddle) {10, 350, LEFT};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {785, 350, RIGHT};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {350, 10, TOP};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {350, 785, BOTTOM};
    }
    return paddle;
}

void move_up(Paddle * paddle)
{
    if (paddle->loc == LEFT || paddle->loc == RIGHT)
    {
        if (paddle->y > 0)
        {
            paddle->y -= DEFAULT_MOVEMENT;
        }
    }
}

void move_down(Paddle * paddle)
{
    if (paddle->loc == LEFT || paddle->loc == RIGHT)
    {
        if (paddle->y < WINDOW_H - PADDLE_H)
        {
            paddle->y += DEFAULT_MOVEMENT;
        }
    }
}

void move_left(Paddle * paddle)
{
    if (paddle->loc == TOP || paddle->loc == BOTTOM)
    {
        if (paddle->x > 0)
        {
            paddle->x -= DEFAULT_MOVEMENT;
        }
    }
}

void move_right(Paddle * paddle)
{
    if (paddle->loc == TOP || paddle->loc == BOTTOM)
    {
        if (paddle->x < WINDOW_W - PADDLE_H)
        {
            paddle->x += DEFAULT_MOVEMENT;
        }
    }
}
