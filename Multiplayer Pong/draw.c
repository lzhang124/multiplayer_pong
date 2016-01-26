//
//  draw.c
//  Multiplayer Pong
//
//

#include "draw.h"
#include "constants.h"

void draw_text(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);
    
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void draw_number(int number, PaddleType paddle_number)
{
    int x;
    int y;
    glColor3f(0.3, 0.3, 0.3);
    
    switch (paddle_number)
    {
        case LEFT:
            x = 270;
            y = 335;
            break;
        case RIGHT:
            x = 820;
            y = 335;
            break;
        case TOP:
            x = 545;
            y = 160;
            break;
        case BOTTOM:
            x = 545;
            y = 510;
            break;
    }
    
    switch (number)
    {
        case 0:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            break;
        case 1:
            glRecti(x + NUMBER_H_M, y, x + NUMBER_H_M + NUMBER_SIZE, y + NUMBER_H);
            break;
        case 2:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_SIZE, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            break;
        case 3:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            break;
        case 4:
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            break;
        case 5:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            break;
        case 6:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_H);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            break;
        case 7:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            break;
        case 8:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_H);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            break;
        case 9:
            glRecti(x, y, x + NUMBER_W, y + NUMBER_SIZE);
            glRecti(x, y, x + NUMBER_SIZE, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x, y + NUMBER_V_M, x + NUMBER_W, y + NUMBER_V_M + NUMBER_SIZE);
            glRecti(x + NUMBER_W - NUMBER_SIZE, y, x + NUMBER_W, y + NUMBER_H);
            glRecti(x, y + NUMBER_H - NUMBER_SIZE, x + NUMBER_W, y + NUMBER_H);
            break;
    }
}
