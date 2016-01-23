//
//  draw.c
//  Multiplayer Pong
//
//  Created by Larry Zhang on 1/22/16.
//
//

#include "draw.h"

void draw_text(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);
    
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void draw_number(int number, float x, float y)
{
    // score drawing
}