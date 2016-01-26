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

const char* NAME = "Pong";

int master_socket;
int paddle_number;
int num_players;
Paddle *paddles[MAX_PLAYERS] = {NULL};
Ball *ball;

int started = FALSE;
int session_ended = FALSE;

int i;

int count = 0;

void delay(int length)
{
    int i;
    while (i < length)
    {
        i++;
    }
}

void update()
{
    ++count;
    if (count == 1000)
    {
        count = 0;
        
        // update paddles
        Message *msg = read_message(master_socket);
        
        if (msg) {
            if (msg->first > MAX_PLAYERS)
            {
                // receiving ball location
                started = TRUE;
                start_ball = TRUE;
                ball = new_ball(msg->BALL_X, msg->BALL_Y, msg->DIRECTION);
            }
            else
            {
                // receiving paddle update
                if (!paddles[msg->PADDLE])
                {
                    paddles[msg->PADDLE] = new_paddle(msg->PADDLE, msg->LOCATION, msg->DIRECTION);
                    num_players++;
                }
                else
                {
                    if (msg->second == -1)
                    {
                        start_ball = FALSE;
                        for (i = 0; i < num_players; i++)
                        {
                            if (i != msg->PADDLE)
                            {
                                paddles[i]->score++;
                            }
                            reset_paddle(paddles[i]);
                        }
                        session_ended = TRUE;
                    }
                    else
                    {
                        update_paddle(paddles[msg->PADDLE], msg->LOCATION, msg->DIRECTION);
                    }
                }
            }
            
            free(msg);
        }
    
        // move the paddles
        for (i = 0; i < num_players; i++) {
            Paddle *paddle = paddles[i];
            move_paddle(paddle);
        }
        
        if (start_ball)
        {
            // move the ball
            if (session_ended)
            {
//                delay(50000);
                sleep(1);
                session_ended = FALSE;
            }
            if (move_ball(ball)) {
                Paddle *paddle = paddles[paddle_number];
                Message msg = {paddle_number, -1, -1};
                switch (paddle_number)
                {
                    case LEFT:
                        if (ball->x == MARGIN &&
                            (ball->y <= paddle->coordinate - BALL_H ||
                             ball->y >= paddle->coordinate + V_PADDLE_H))
                        {
                            write_message(master_socket, &msg);
                        }
                        break;
                    case RIGHT:
                        if (ball->x == WINDOW_W - MARGIN - BALL_W &&
                            (ball->y <= paddle->coordinate - BALL_H ||
                             ball->y >= paddle->coordinate + V_PADDLE_H))
                        {
                            write_message(master_socket, &msg);
                        }
                        break;
                    case TOP:
                        if (ball->y == MARGIN &&
                            (ball->x <= paddle->coordinate - BALL_W ||
                             ball->x >= paddle->coordinate + H_PADDLE_W))
                        {
                            write_message(master_socket, &msg);
                        }
                        break;
                    case BOTTOM:
                        if (ball->y == WINDOW_H - MARGIN - BALL_H &&
                            (ball->x <= paddle->coordinate - BALL_W ||
                             ball->x >= paddle->coordinate + H_PADDLE_W))
                        {
                            write_message(master_socket, &msg);
                        }
                        break;
                }
            }
        }
        
        // redraw the window
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // start button
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
        
        switch (paddle->type) {
            case LEFT:
                glRecti(PADDLE_L, paddle->coordinate, PADDLE_L + V_PADDLE_W, paddle->coordinate + V_PADDLE_H);
                break;
            case RIGHT:
                glRecti(PADDLE_R, paddle->coordinate, PADDLE_R + V_PADDLE_W, paddle->coordinate + V_PADDLE_H);
                break;
            case TOP:
                glRecti(paddle->coordinate, PADDLE_T, paddle->coordinate + H_PADDLE_W, PADDLE_T + H_PADDLE_H);
                break;
            case BOTTOM:
                glRecti(paddle->coordinate, PADDLE_B, paddle->coordinate + H_PADDLE_W, PADDLE_B + H_PADDLE_H);
                break;
        }
    }
    
    // ball
    if (start_ball) {
        glColor3f(1.0, 1.0, 1.0);
        glRecti(ball->x, ball->y, ball->x + BALL_W, ball->y + BALL_H);
    }
    
    // scores
    if (started) {
        glColor3f(0.3, 0.3, 0.3);
        for (i = 0; i < num_players; i++)
        {
            draw_number(paddles[i]->score, i);
        }
    }
    
    glutSwapBuffers();
}

void mouse_function(int button, int state, int xscr, int yscr)
{
    if (!started)
    {
        if (xscr > 550 && xscr < 592 && yscr > 365 && yscr < 382)
        {
            // send start message to server
            Message msg = START_MESSAGE;
            write_message(master_socket, &msg);
        }
    }
}

void special_pressed(int key, int xscr, int yscr)
{
    Paddle *paddle = paddles[paddle_number];
    switch (key)
    {
        case GLUT_KEY_DOWN:
            paddle->direction = SOUTH;
            break;
        case GLUT_KEY_UP:
            paddle->direction = NORTH;
            break;
        case GLUT_KEY_LEFT:
            paddle->direction = WEST;
            break;
        case GLUT_KEY_RIGHT:
            paddle->direction = EAST;
            break;
    }
    Message msg = {paddle_number, paddle->coordinate, paddle->direction};
    write_message(master_socket, &msg);
}

void special_released(int key, int xscr, int yscr)
{
    int stopped = FALSE;
    Paddle *paddle = paddles[paddle_number];
    switch (key)
    {
        case GLUT_KEY_DOWN:
            if (paddle->direction == SOUTH)
            {
                paddle->direction = NONE;
                stopped = TRUE;
            }
            break;
        case GLUT_KEY_UP:
            if (paddle->direction == NORTH)
            {
                paddle->direction = NONE;
                stopped = TRUE;
            }
            break;
        case GLUT_KEY_LEFT:
            if (paddle->direction == WEST)
            {
                paddle->direction = NONE;
                stopped = TRUE;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (paddle->direction == EAST)
            {
                paddle->direction = NONE;
                stopped = TRUE;
            }
            break;
    }
    
    if (stopped) {
        Message msg = {paddle_number, paddle->coordinate, NONE};
        write_message(master_socket, &msg);
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
    
    // get paddle
    Message *msg = read_message(master_socket);
    if (msg)
    {
        paddle_number = msg->PADDLE;
        num_players = paddle_number + 1;
        paddles[paddle_number] = new_paddle(paddle_number, msg->LOCATION, msg->DIRECTION);
        
        for (i = 0; i < paddle_number; i++)
        {
            msg = read_message(master_socket);
            paddles[i] = new_paddle(i, msg->LOCATION, msg->DIRECTION);
        }
        free(msg);
    }
    else
    {
        end_connection(master_socket);
        exit(0);
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
    glutSpecialFunc(special_pressed);
    glutSpecialUpFunc(special_released);
    glutReshapeFunc(resize);
    glutWMCloseFunc(close_window);
    
    // start
    glutMainLoop();
}
