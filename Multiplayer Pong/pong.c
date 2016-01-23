//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "paddle.h"
#include "client.h"

#define FALSE 0
#define TRUE 1

const char* NAME = "Pong";
unsigned const int WINDOW_START_X = 300;
unsigned const int WINDOW_START_Y = 50;

int master_socket;
Paddle *paddle;

unsigned int ball_x = 400;
unsigned int ball_y = 400;

int down_pressed = FALSE;
int up_pressed = FALSE;
int left_pressed = FALSE;
int right_pressed = FALSE;


int count = 0;
void update()
{
    ++count;
    if (count == 5000)
    {
        count = 0;
        
        // move the paddle
        if (down_pressed)
        {
            move_down(paddle);
        }
        else if (up_pressed)
        {
            move_up(paddle);
        }
        else if (left_pressed)
        {
            move_left(paddle);
        }
        else if (right_pressed)
        {
            move_right(paddle);
        }
        
        // redraw the window
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // paddles
    if (paddle->loc == LEFT || paddle->loc == RIGHT) {
        glRecti(paddle->x, paddle->y, paddle->x + PADDLE_W, paddle->y + PADDLE_H);
    }
    else if (paddle->loc == TOP || paddle->loc == BOTTOM)
    {
        glRecti(paddle->x, paddle->y, paddle->x + PADDLE_H, paddle->y + PADDLE_W);
    }
    
    // ball
    
    
    glutSwapBuffers();
}

//void mouse_function(int button, int state, int xscr, int yscr)
//{
//    if (state == GLUT_DOWN) {
//        if (button == GLUT_LEFT_BUTTON)
//        {
//            printf("Left mouse clicked.\n");
//        }
//        else if (button == GLUT_RIGHT_BUTTON)
//        {
//            printf("Right mouse clicked.\n");
//        }
//    }
//}
//
//void motion_function(int xscr, int yscr)
//{
//    printf("Motion (%d, %d).\n", xscr, yscr);
//}
//
void key_pressed(unsigned char key, int xscr, int yscr)
{
    printf("Key %c pressed.\n", key);
}

void special_pressed(int key, int xscr, int yscr)
{
    if (key == GLUT_KEY_UP)
    {
        up_pressed = TRUE;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        down_pressed = TRUE;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        left_pressed = TRUE;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        right_pressed = TRUE;
    }
}

void special_released(int key, int xscr, int yscr)
{
    if (key == GLUT_KEY_UP)
    {
        up_pressed = FALSE;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        down_pressed = FALSE;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        left_pressed = FALSE;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        right_pressed = FALSE;
    }
}

void close_window()
{
    free(paddle);
    end_connection(master_socket);
    exit(0);
}

void set_viewport()
{
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_W, WINDOW_H, 0);
    glMatrixMode(GL_MODELVIEW);
}

void pong(int argc, char *argv[], char *server_name[], int port_num)
{
    master_socket = start_client(server_name, port_num);
    
    // get paddle number
//    int paddle_number = read_number(master_socket);
//    paddle = set_paddle(paddle_number);
    paddle = set_paddle(TOP);
    
    // init glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    // window
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitWindowPosition(WINDOW_START_X, WINDOW_START_Y);
    glutCreateWindow(NAME);
    
    // background
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glShadeModel(GL_SMOOTH);
    set_viewport();
    
    // define functions
    glutIgnoreKeyRepeat(1);
    glutIdleFunc(update);
    glutDisplayFunc(display);
//    glutMouseFunc(mouse_function);
//    glutMotionFunc(motion_function);
    glutKeyboardFunc(key_pressed);
    glutSpecialFunc(special_pressed);
    glutSpecialUpFunc(special_released);
    glutWMCloseFunc(close_window);
    
    // start
    glutMainLoop();
}
