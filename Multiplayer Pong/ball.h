//
//  ball.h
//  Multiplayer Pong
//
//

#ifndef ball_h
#define ball_h

#include <stdlib.h>
#include <time.h>

typedef enum
{
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT,
    UP_RIGHT
} BallDir;

typedef struct
{
    int x;
    int y;
    BallDir direction;
} Ball;

Ball * add_ball();
void update_ball(Ball * ball);

#endif /* ball_h */
