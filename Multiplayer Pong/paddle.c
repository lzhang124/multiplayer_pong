//
//  paddle.c
//  Multiplayer Pong
//
//

#include "paddle.h"
#include "constants.h"

Paddle * new_paddle(int paddle_number, int location, PaddleDir direction)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    if (paddle_number == LEFT)
    {
        *paddle = (Paddle) {10, location, LEFT, direction};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {1120, location, RIGHT, direction};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {location, 10, TOP, direction};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {location, 720, BOTTOM, direction};
    }
    return paddle;
}

void move_up(Paddle * paddle)
{
    if (paddle->type == LEFT || paddle->type == RIGHT)
    {
        if (paddle->y >= MARGIN + PADDLE_MOVEMENT)
        {
            paddle->y -= PADDLE_MOVEMENT;
        }
    }
}

void move_down(Paddle * paddle)
{
    if (paddle->type == LEFT || paddle->type == RIGHT)
    {
        if (paddle->y <= WINDOW_H - MARGIN - V_PADDLE_H - PADDLE_MOVEMENT)
        {
            paddle->y += PADDLE_MOVEMENT;
        }
    }
}

void move_left(Paddle * paddle)
{
    if (paddle->type == TOP || paddle->type == BOTTOM)
    {
        if (paddle->x >= MARGIN + PADDLE_MOVEMENT)
        {
            paddle->x -= PADDLE_MOVEMENT;
        }
    }
}

void move_right(Paddle * paddle)
{
    if (paddle->type == TOP || paddle->type == BOTTOM)
    {
        if (paddle->x <= WINDOW_W - MARGIN - H_PADDLE_W - PADDLE_MOVEMENT)
        {
            paddle->x += PADDLE_MOVEMENT;
        }
    }
}
