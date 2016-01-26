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
#include "message.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

void pong(int argc, char *argv[], char *server_name[], int port_num);

#endif /* pong_h */
