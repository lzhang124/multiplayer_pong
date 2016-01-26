//
//  draw.h
//  Multiplayer Pong
//
//

#ifndef draw_h
#define draw_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "paddle.h"

void draw_text(char *string, float x, float y);
void draw_number(int number, PaddleType paddle_number);

#endif /* draw_h */
