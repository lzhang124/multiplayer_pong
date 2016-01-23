//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "constants.h"
#include "paddle.h"
#include "ball.h"
#include "client.h"
#include "draw.h"

#define FALSE 0
#define TRUE 1

const char* NAME = "Pong";

int master_socket;
int paddle_number;
int num_players;
Paddle *paddles[MAX_PLAYERS];
Ball *ball;

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
    if (count == 1000)
    {
        count = 0;
    
        // move the paddle
        Paddle *paddle = paddles[paddle_number];
        if (down_pressed)
        {
            move_down(paddle);
//            write_number(master_socket, paddle->y);
        }
        else if (up_pressed)
        {
            move_up(paddle);
//            write_number(master_socket, paddle->y);
        }
        else if (left_pressed)
        {
            move_left(paddle);
//            write_number(master_socket, paddle->x);
        }
        else if (right_pressed)
        {
            move_right(paddle);
//            write_number(master_socket, paddle->x);
        }
        
        // move the ball
        if (started)
        {
            update_ball(ball);
        }
        else
        {
            int new_num_players = read_number(master_socket);
            if (new_num_players != -1)
            {
                num_players = new_num_players;
                paddles[num_players - 1] = add_paddle(num_players - 1);
            }
        }
        
        // redraw the window
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!started)
    {
        glColor3f(1.0, 1.0, 1.0);
        draw_text("Start", 400, 420);
    }
    
    // paddles
    for (i = 0; i < num_players; i++)
    {
        Paddle *paddle = paddles[i];
        if (i == paddle_number)
        {
            glColor3f(1.0, 1.0, 1.0);
        }
        else {
            glColor3f(0.3, 0.3, 0.3);
        }
        
        if (paddle->type == LEFT || paddle->type == RIGHT)
        {
            glRecti(paddle->x, paddle->y, paddle->x + PADDLE_W, paddle->y + PADDLE_H);
        }
        else if (paddle->type == TOP || paddle->type == BOTTOM)
        {
            glRecti(paddle->x, paddle->y, paddle->x + PADDLE_H, paddle->y + PADDLE_W);
        }
    }
    
    // ball
    if (started) {
        glColor3f(1.0, 1.0, 1.0);
        glRecti(ball->x, ball->y, ball->x + BALL_W, ball->y + BALL_H);
    }
    
    glutSwapBuffers();
}

void mouse_function(int button, int state, int xscr, int yscr)
{
    if (!started)
    {
        if (xscr > 400 && xscr < 440 && yscr > 405 && yscr < 425)
        {
            started = TRUE;
            ball = add_ball();
        }
    }
}

//void key_pressed(unsigned char key, int xscr, int yscr)
//{
//    printf("Key %c pressed.\n", key);
//}

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
    free(ball);
    for (i = 0; i < num_players; i++)
    {
        Paddle *paddle = paddles[i];
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
    paddle_number = read_number(master_socket);
    num_players = paddle_number + 1;
    
    for (i = 0; i <= paddle_number; i++)
    {
        paddles[i] = add_paddle(i);
    }
    
    // set master_socket so that reads/writes don't block
    fcntl(master_socket, F_SETFL, O_NONBLOCK);
    
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
//    glutKeyboardFunc(key_pressed);
    glutSpecialFunc(special_pressed);
    glutSpecialUpFunc(special_released);
    glutWMCloseFunc(close_window);
    
    // start
    glutMainLoop();
}
