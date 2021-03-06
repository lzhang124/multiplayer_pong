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

void send_all_other_paddles(Game *game, int paddle_number)
{
    int i;
    Message msg;
    Paddle **paddles = game->paddles;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (i != paddle_number && paddles[i])
        {
            msg = (Message) {paddles[i]->type, paddles[i]->coordinate, paddles[i]->direction};
            send_message(paddle_number, &msg);
        }
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

void end_game(Game *game, int master_socket)
{
    free(game->ball);
    free(game);
    end_connection(master_socket);
}

int check_start_signal(Message *msg)
{
    return msg->first == -1;
}

int check_ball_hit(Message *msg)
{
    return msg->second == -1;
}

int update_scores(Game *game, int paddle_number)
{
    int end_game = FALSE;
    
    // losing paddle +0, all others +1
    int i;
    for (i = 0; i < game->number_players; i++)
    {
        reset_paddle(game->paddles[i]);
        if (i != paddle_number)
        {
            if (++(game->paddles[i]->score) == MAX_SCORE)
            {
                end_game = TRUE;
            }
        }
    }
    return end_game;
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
    
    while (TRUE)
    {
        if (!game->started)
        {
            // wait for players to join game
            if (wait_for_connection(master_socket))
            {
                if (game->number_players >= MAX_PLAYERS)
                {
                    add_connection(master_socket, FALSE);
                }
                else
                {
                    int paddle_number = add_connection(master_socket, TRUE);
                    add_paddle(game, paddle_number);
                    send_all_other_paddles(game, paddle_number);
                }
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
                    if (check_start_signal(msg))
                    {
                        game->started = TRUE;

                        // reset scores
                        int i;
                        for (i = 0; i < game->number_players; i++) {
                            game->paddles[i]->score = 0;
                        }
                        start_ball(game);
                    }
                    else
                    {
                        update_paddle(game->paddles[paddle_number], msg->LOCATION, msg->DIRECTION);
                        notify_others(paddle_number, msg);
                    }
                    free(msg);
                }
            }
        }
        else
        {
            if (wait_for_connection(master_socket))
            {
                add_connection(master_socket, FALSE);
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
                    // check if message is for a ball missing a paddle
                    if (check_ball_hit(msg))
                    {
                        notify_all(msg);
                        if (update_scores(game, msg->PADDLE)) {
                            game->started = FALSE;
                            Message msg = START_MESSAGE;
                            notify_all(&msg);
                            continue;
                        }
                        
                        sleep(1);
                        reset_ball(game->ball);
                        start_ball(game);
                    }
                    else
                    {
                        update_paddle(game->paddles[paddle_number], msg->LOCATION, msg->DIRECTION);
                        notify_others(paddle_number, msg);
                    }
                    free(msg);
                }
            }
        }
        
        // close the server when no more clients
        if (game->number_players == 0)
        {
            end_game(game, master_socket);
            exit(0);
        }
    }
}
