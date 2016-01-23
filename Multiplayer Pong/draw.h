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

void draw_text(char *string, float x, float y);
void draw_number(int number, float x, float y);

#endif /* draw_h */
