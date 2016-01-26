//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "server.h"

Game * init_game()
{
    Ball *ball = new_ball();
    Game *game = malloc(sizeof(*game));
    *game = (Game) {0, {NULL}, ball, FALSE};
    
    return game;
}

void add_paddle(Game *game, int paddle_number)
{
    Paddle *paddle = new_paddle(paddle_number);
    
    game->paddles[paddle_number] = paddle;
    game->number_players++;
    
    // notify all players of new player
    Message msg = {paddle_number, paddle->coordinate, NONE};
    notify_all(&msg);
}

void send_previous_paddles(Game *game, int paddle_number)
{
    int i;
    Message msg;
    Paddle **paddles = game->paddles;
    for (i = 0; i < paddle_number; i++)
    {
        msg = (Message) {paddles[i]->type, paddles[i]->coordinate, paddles[i]->direction};
        send_message(paddle_number, &msg);
    }
}

void remove_paddle(Game *game, int paddle_number)
{
    // free paddle and player
    Paddle *paddle = game->paddles[paddle_number];
    free(paddle);
    
    game->paddles[paddle_number] = NULL;
    game->number_players--;
}

void end_game(Game *game)
{
    free(game->ball);
    free(game);
}

int check_start_signal(Message *msg)
{
    return msg->first == -1;
}

void start_ball(Game *game)
{
    // send all players ball location
    Ball *ball = game->ball;
    Message msg = {ball->x, ball->y, ball->direction};
    notify_all(&msg);
}

void pong(int port_num)
{
    int master_socket = start_server(port_num);
    Game *game = init_game();
    
    while(game->number_players < MAX_PLAYERS && !game->started)
    {
        // wait for players to join game
        if (wait_for_connection(master_socket))
        {
            int paddle_number = add_connection(master_socket);
            add_paddle(game, paddle_number);
            send_previous_paddles(game, paddle_number);
        }
        else
        {
            int paddle_number = check_socket();
            Message *msg = read_message(paddle_number);
            if (msg == NULL)
            {
                remove_paddle(game, paddle_number);
            }
            else
            {
                // check if message is a start signal
                if (check_start_signal(msg) == 1)
                {
                    start_ball(game);
                }
                else
                {
                    // send info to other players
                    update_paddle(game->paddles[paddle_number], msg->LOCATION, msg->DIRECTION);
                    notify_others(paddle_number, msg);
                }
                free(msg);
            }
        }
        
        // close the server when no more clients
        if (game->number_players == 0)
        {
            end_game(game);
            end_connection(master_socket);
            break;
        }
    }
}
