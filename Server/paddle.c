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
        *paddle = (Paddle) {10, LEFT, NONE};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {1120, RIGHT, NONE};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {10, TOP, NONE};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {720, BOTTOM, NONE};
    }
    return paddle;
}

void update_paddle(Paddle * paddle, int location, PaddleDir direction)
{
    paddle->coordinate = location;
    paddle->direction = direction;
}
