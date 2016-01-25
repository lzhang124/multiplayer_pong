//
//  paddle.c
//  Multiplayer Pong
//
//

#include "paddle.h"
#include "constants.h"

Paddle * add_paddle(int paddle_number)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    if (paddle_number == LEFT)
    {
        *paddle = (Paddle) {10, 363, LEFT, NONE};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {1220, 363, RIGHT, NONE};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {543, 10, TOP, NONE};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {543, 820, BOTTOM, NONE};
    }
    return paddle;
}

void move_up(Paddle * paddle)
{
    if (paddle->type == LEFT || paddle->type == RIGHT)
    {
        if (paddle->y >= MARGIN + V_PADDLE_MOVEMENT)
        {
            paddle->y -= V_PADDLE_MOVEMENT;
        }
    }
}

void move_down(Paddle * paddle)
{
    if (paddle->type == LEFT || paddle->type == RIGHT)
    {
        if (paddle->y <= WINDOW_H - MARGIN - V_PADDLE_H - V_PADDLE_MOVEMENT)
        {
            paddle->y += V_PADDLE_MOVEMENT;
        }
    }
}

void move_left(Paddle * paddle)
{
    if (paddle->type == TOP || paddle->type == BOTTOM)
    {
        if (paddle->x >= MARGIN + H_PADDLE_MOVEMENT)
        {
            paddle->x -= H_PADDLE_MOVEMENT;
        }
    }
}

void move_right(Paddle * paddle)
{
    if (paddle->type == TOP || paddle->type == BOTTOM)
    {
        if (paddle->x <= WINDOW_W - MARGIN - H_PADDLE_W - H_PADDLE_MOVEMENT)
        {
            paddle->x += H_PADDLE_MOVEMENT;
        }
    }
}
