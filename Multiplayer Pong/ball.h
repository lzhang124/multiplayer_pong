//
//  ball.h
//  Multiplayer Pong
//
//

#ifndef ball_h
#define ball_h

#include <stdlib.h>
#include <time.h>

enum ball_dir
{
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT,
    UP_RIGHT
};

typedef struct
{
    int x;
    int y;
    enum ball_dir direction;
} Ball;

Ball * add_ball();
void update_ball(Ball * ball);

#endif /* ball_h */
