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
        *paddle = (Paddle) {location, LEFT, direction, 0};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {location, RIGHT, direction, 0};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {location, TOP, direction, 0};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {location, BOTTOM, direction, 0};
    }
    return paddle;
}

void update_paddle(Paddle * paddle, int location, PaddleDir direction)
{
    if (paddle->type == LEFT || paddle->type == RIGHT)
    {
        paddle->coordinate = location;
    }
    else if (paddle->type == TOP || paddle->type == BOTTOM)
    {
        paddle->coordinate = location;
    }
    paddle->direction = direction;
}

void move_paddle(Paddle * paddle)
{
    switch (paddle->direction)
    {
        case NORTH:
            if (paddle->type == LEFT || paddle->type == RIGHT)
            {
                if (paddle->coordinate >= MARGIN + PADDLE_MOVEMENT)
                {
                    paddle->coordinate -= PADDLE_MOVEMENT;
                }
            }
            break;
        case SOUTH:
            if (paddle->type == LEFT || paddle->type == RIGHT)
            {
                if (paddle->coordinate <= WINDOW_H - MARGIN - V_PADDLE_H - PADDLE_MOVEMENT)
                {
                    paddle->coordinate += PADDLE_MOVEMENT;
                }
            }
            break;
        case WEST:
            if (paddle->type == TOP || paddle->type == BOTTOM)
            {
                if (paddle->coordinate >= MARGIN + PADDLE_MOVEMENT)
                {
                    paddle->coordinate -= PADDLE_MOVEMENT;
                }
            }
            break;
        case EAST:
            if (paddle->type == TOP || paddle->type == BOTTOM)
            {
                if (paddle->coordinate <= WINDOW_W - MARGIN - H_PADDLE_W - PADDLE_MOVEMENT)
                {
                    paddle->coordinate += PADDLE_MOVEMENT;
                }
            }
            break;
        case NONE:
            break;
    }
}
