//
//  pong.h
//  Multiplayer Pong
//
//

#ifndef pong_h
#define pong_h

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

void pong(int argc, char *argv[]);

#ifndef __MAC__
#define __MAC__ 1
#endif

#ifdef __MAC__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

unsigned window_x = 800;
unsigned window_y = 800;


void displayfunct()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
}

#endif /* pong_h */
