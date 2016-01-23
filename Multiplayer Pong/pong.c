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
const int WINDOW_START_X = 300;
const int WINDOW_START_Y = 50;
const int MAX_PLAYERS = 4;

int master_socket;
int paddle_num;
int num_players;
Paddle paddles[MAX_PLAYERS];

int ball_x = 400;
int ball_y = 400;

int started = FALSE;
int down_pressed = FALSE;
int up_pressed = FALSE;
int left_pressed = FALSE;
int right_pressed = FALSE;

int i;

int count = 0;
void update()
{
    ++count;
    if (count == 5000)
    {
        count = 0;
        
        if (started)
        {
            Paddle *paddle = &paddles[paddle_num];
            
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
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // paddles
    if (started) {
        for (i = 0; i < num_players; i++)
        {
            Paddle *paddle = &paddles[i];
            if (i == paddle_num)
            {
                glColor3f(1.0, 0.0, 0.0);
            }
            
            if (paddle->loc == LEFT || paddle->loc == RIGHT)
            {
                glRecti(paddle->x, paddle->y, paddle->x + PADDLE_W, paddle->y + PADDLE_H);
            }
            else if (paddle->loc == TOP || paddle->loc == BOTTOM)
            {
                glRecti(paddle->x, paddle->y, paddle->x + PADDLE_H, paddle->y + PADDLE_W);
            }
        }
    }
    
    // ball
    
    
    glutSwapBuffers();
}

void mouse_function(int button, int state, int xscr, int yscr)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        printf("Left mouse clicked.\n");
    }
}

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
    for (i = 0; i < num_players; i++) {
        Paddle *paddle = &paddles[i];
        free(paddle);
    }
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
    paddle_num = read_number(master_socket);
    
    // get number of players
    num_players = read_number(master_socket);
    
    for (i = 0; i < num_players; i++) {
        paddles[i] = *set_paddle(i);
    }
    
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
    glutMouseFunc(mouse_function);
    glutKeyboardFunc(key_pressed);
    glutSpecialFunc(special_pressed);
    glutSpecialUpFunc(special_released);
    glutWMCloseFunc(close_window);
    
    // start
    glutMainLoop();
}
