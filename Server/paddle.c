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
        *paddle = (Paddle) {10, 314, LEFT, NONE};
    }
    else if (paddle_number == RIGHT)
    {
        *paddle = (Paddle) {1120, 314, RIGHT, NONE};
    }
    else if (paddle_number == TOP)
    {
        *paddle = (Paddle) {495, 10, TOP, NONE};
    }
    else if (paddle_number == BOTTOM)
    {
        *paddle = (Paddle) {495, 720, BOTTOM, NONE};
    }
    return paddle;
}
