//
//  paddle.h
//  Multiplayer Pong
//
//  Created by Larry Zhang on 1/22/16.
//
//

#ifndef paddle_h
#define paddle_h

#include <stdlib.h>

typedef struct
{
    int x;
    int y;
    int loc;
} Paddle;

enum paddle_type
{
    LEFT, RIGHT, TOP, BOTTOM
};

Paddle * add_paddle(int paddle_number);
void move_up(Paddle * paddle);
void move_down(Paddle * paddle);
void move_left(Paddle * paddle);
void move_right(Paddle * paddle);

#endif /* paddle_h */
