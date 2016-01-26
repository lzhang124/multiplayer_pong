//
//  paddle.h
//  Multiplayer Pong
//
//

#ifndef paddle_h
#define paddle_h

#include <stdlib.h>

typedef enum
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} PaddleType;

typedef enum
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NONE
} PaddleDir;

typedef struct
{
    int coordinate;
    PaddleType type;
    PaddleDir direction;
} Paddle;

Paddle * new_paddle(int paddle_number);
void update_paddle(Paddle * paddle, int location, PaddleDir direction);

#endif /* paddle_h */
