//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "server.h"

Game * init_game()
{
    Ball *ball = malloc(sizeof(*ball));
    Game *game = malloc(sizeof(*game));
    *game = (Game) {0, {NULL}, ball};
    
    return game;
}

void add_player(Game * game, int player_number)
{
    Paddle *paddle = malloc(sizeof(*paddle));
    Player *player = malloc(sizeof(*player));
    *player = (Player) {player_number, 0, paddle};
    
    game->players[player_number] = player;
    game->number_players++;
}

void remove_player(Game * game, int player_number)
{
    Player *player = game->players[player_number];
    free(player->paddle);
    free(player);
    game->players[player_number] = NULL;
    game->number_players--;
}

void end_game(Game * game)
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
            
            // send paddle number
            send_number(player_number, player_number);
        }
        else
        {
            int player_number = check_socket();
            char *buffer;
            buffer = read_string(player_number);
            if (buffer == '\0') {
                printf(")disconnect");
                remove_player(game, player_number);
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
