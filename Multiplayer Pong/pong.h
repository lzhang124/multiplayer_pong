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
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

void generate_texture();
void loadTextures();
void display();
void drawScene();
void idle();
void setCamera();
void makeMenu();
void menuCallback(int option);
void CreateGlutWindow();
void CreateGlutCallbacks();
void InitOpenGL();
void ExitGlut();
void pong(int argc, char *argv[]);

#endif /* pong_h */
