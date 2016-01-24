//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "server.h"

Game *init_game()
{
    Ball *ball = malloc(sizeof(*ball));
    Game *game = malloc(sizeof(*game));
    *game = (Game) {0, {NULL}, ball};
    
    return game;
}

void add_player(Game *game, int player_number)
{
    // MODIFY COORDS
    Paddle *paddle = malloc(sizeof(*paddle));
    *paddle = (Paddle) {10, 10, LEFT + player_number};
    
    Player *player = malloc(sizeof(*player));
    *player = (Player) {player_number, 0, paddle};
    
    game->players[player_number] = player;
    game->number_players++;
    
    // notify other players of new player through updated num_players
    notify_clients_number(player_number, game->number_players);
}

void remove_player(Game *game, int player_number)
{
    // free paddle and player
    Player *player = game->players[player_number];
    free(player->paddle);
    free(player);
    
    game->players[player_number] = NULL;
    game->number_players--;
}

void end_game(Game *game)
{
    free(game->ball);
    free(game);
}

void pong(int port_num)
{
    int master_socket = start_server(port_num);
    Game *game = init_game();
    
    while(game->number_players < MAX_PLAYERS)
    {
        // wait for players to join game
        if (wait_for_connection(master_socket) == 1)
        {
            int player_number = add_connection(master_socket);
            add_player(game, player_number);
    
            // send paddle type to new player
            send_number(player_number, player_number);
        }
        else
        {
            int player_number = check_socket();
            Paddle *paddleToSend = (Paddle *) read_string(player_number);
            if (paddleToSend == NULL)
            {
                remove_player(game, player_number);
            }
            else
            {
                printf("paddle to send: %d\n", paddleToSend->type);
                printf("paddle coord to send: %d, %d\n", paddleToSend->x, paddleToSend->y);
                // send info to other players
                notify_clients_string(player_number, paddleToSend);
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
