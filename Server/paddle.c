//
//  paddle.c
//  Multiplayer Pong
//
//

#include "paddle.h"
#include "constants.h"

Paddle * new_paddle(int paddle_number)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    if (paddle_number == LEFT)
    {
        *paddle = (Paddle) {V_PADDLE_START, LEFT, NONE, 0};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {V_PADDLE_START, RIGHT, NONE, 0};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {H_PADDLE_START, TOP, NONE, 0};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {H_PADDLE_START, BOTTOM, NONE, 0};
    }
    return paddle;
}

void update_paddle(Paddle * paddle, int location, PaddleDir direction)
{
    paddle->coordinate = location;
    paddle->direction = direction;
}

void reset_paddle(Paddle *paddle)
{
    if (paddle->type == LEFT)
    {
        *paddle = (Paddle) {V_PADDLE_START, LEFT, NONE, 0};
    }
    else if (paddle->type == RIGHT)
    {
        *paddle = (Paddle) {V_PADDLE_START, RIGHT, NONE, 0};
    }
    else if (paddle->type == TOP)
    {
        *paddle = (Paddle) {H_PADDLE_START, TOP, NONE, 0};
    }
    else if (paddle->type == BOTTOM)
    {
        *paddle = (Paddle) {H_PADDLE_START, BOTTOM, NONE, 0};
    }
}
