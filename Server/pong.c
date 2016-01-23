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
    // GUI: adds in new paddle
    notify_players_number(game->number_players, player_number);
}

void remove_player(Game *game, int player_number)
{
    // free paddle and player
    Player *player = game->players[player_number];
    free(player->paddle);
    free(player);
    
    game->players[player_number] = NULL;
    game->number_players--;
    
    // notify other players of new player through updated num_players
    // GUI: converts to wall
    notify_players_number(game->number_players, player_number);
}

void end_game(Game *game)
{
    free(game->ball);
    free(game);
}

void notify_players_number(int message, int from_player_number)
{
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (i != from_player_number)
        {
        	send_number(i, message);
        }
    }
}

void notify_players_string(char *message, int from_player_number)
{
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (i != from_player_number)
        {
            send_string(i, message);
        }
    }
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
            char *buffer = read_string(player_number);
            if (buffer == NULL)
            {
                remove_player(game, player_number);
            }
            else
            {
                // send info to other players
                notify_players_string(buffer, player_number);
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