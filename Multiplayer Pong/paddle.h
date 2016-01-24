//
//  paddle.h
//  Multiplayer Pong
//
//

#ifndef paddle_h
#define paddle_h

#include <stdlib.h>
//#include <rpc/xdr.h>

#pragma pack(1)
typedef enum
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} PaddleType;

typedef struct
{
    int x;
    int y;
    PaddleType type;
} Paddle;
#pragma pack(0)

//bool_t xdr_Paddle(XDR *xdrs, Paddle *paddle)
//{
//    return(xdr_int(xdrs, paddle->x) &&
//           xdr_int(xdrs, paddle->y) &&
//           xdr_enum(xdrs, paddle->type));
//}

Paddle *add_paddle(int paddle_number);
void move_up(Paddle * paddle);
void move_down(Paddle * paddle);
void move_left(Paddle * paddle);
void move_right(Paddle * paddle);

#endif /* paddle_h */
