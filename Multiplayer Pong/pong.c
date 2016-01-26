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
Paddle *paddles[MAX_PLAYERS] = {NULL};
Ball *ball;

int started = FALSE;
int key_pressed = -1;

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
        if (key_pressed != -1)
        {
            switch (key_pressed)
            {
                case GLUT_KEY_DOWN :
                    move_down(paddle);
                    break;
                case GLUT_KEY_UP :
                    move_up(paddle);
                    break;
                case GLUT_KEY_LEFT :
                    move_left(paddle);
                    break;
                case GLUT_KEY_RIGHT :
                    move_right(paddle);
                    break;
            }
        }
        
        // move the ball
        if (started)
        {
            update_ball(ball);
        }
        else
        {

//            Message *msg;
//            read_message(master_socket, msg);
//            int message_paddle = msg->PADDLE;
////            int message_location = msg->LOCATION;
////            int message_direction = msg->DIRECTION;
//            
//            if (message_paddle == -1)
//            {
//                started = TRUE;
//            }
//            else
//            {
//                if (!paddles[message_paddle])
//                {
//                    paddles[message_paddle] = add_paddle(message_paddle);
//                    num_players++;
//                }
//                else
//                {
////                    update_paddle(message_paddle, message_location, message_direction);
//                }
//            }
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
        draw_text("Start", 550, 380);
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
            glRecti(paddle->x, paddle->y, paddle->x + V_PADDLE_W, paddle->y + V_PADDLE_H);
        }
        else if (paddle->type == TOP || paddle->type == BOTTOM)
        {
            glRecti(paddle->x, paddle->y, paddle->x + H_PADDLE_W, paddle->y + H_PADDLE_H);
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
        if (xscr > 550 && xscr < 592 && yscr > 365 && yscr < 382)
        {
            started = TRUE;
            ball = add_ball();
//
//            // send start message to server to send to other players
//            Message msg = {-1, -1, -1};
//            write_message(master_socket, &msg);
        }
    }
}

//void key_pressed(unsigned char key, int xscr, int yscr)
//{
//    printf("Key %c pressed.\n", key);
//}

void special_pressed(int key, int xscr, int yscr)
{
    key_pressed = key;
}

void special_released(int key, int xscr, int yscr)
{
    if (key == key_pressed) {
        key_pressed = -1;
    }
}

void resize(int width, int height)
{
    glutReshapeWindow(WINDOW_W, WINDOW_H);
}

void close_window()
{
    if (started)
    {
        free(ball);
    }
    
    for (i = 0; i < num_players; i++)
    {
        Paddle *paddle = paddles[i];
        free(paddle);
    }
//    end_connection(master_socket);
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
//    master_socket = start_client(server_name, port_num);
    
    // get paddle number
//    Message *msg;
//	read_message(master_socket, msg);
//    int paddle_number = msg->PADDLE;
    paddle_number = 3;
    num_players = paddle_number + 1;
    
    for (i = 0; i <= paddle_number; i++)
    {
        paddles[i] = add_paddle(i);
    }
    
    // set master_socket so that reads/writes don't block
//    fcntl(master_socket, F_SETFL, O_NONBLOCK);
    
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
    glutReshapeFunc(resize);
    glutWMCloseFunc(close_window);
    
    // start
    glutMainLoop();
}
