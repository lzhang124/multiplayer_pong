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
    Paddle *paddle = add_paddle(player_number);
    
    Player *player = malloc(sizeof(*player));
    *player = (Player) {player_number, 0, paddle};
    
    game->players[player_number] = player;
    game->number_players++;
    
    // notify all players of new player
    // bogus location since all clients should know the initial location
    Message msg = {player_number, 400, NONE};
    notify_all(&msg);
}

void update_player(Game *game, int player_number)
{
    
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
            update_player(game, player_number);
        }
        else
        {
            int player_number = check_socket();
            Message *msg;
            read_message(player_number, msg);
            if (msg == NULL)
            {
                remove_player(game, player_number);
            }
            else
            {
                // send info to other players
                notify_others(player_number, msg);
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

void send_start_signal()
{
    
}
