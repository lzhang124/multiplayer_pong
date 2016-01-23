//
//  pong.c
//  Multiplayer Pong
//
//

#include "pong.h"
#include "server.h"

Game *init_game(int server_socket, int server_port)
{
    // create and start game
    Game *game = malloc(sizeof(*game));
    game->server_port = server_port;
    game->server_socket = server_socket;
    game->number_players = 0;
    
    game->players = (Player *)calloc(MAX_PLAYERS, sizeof(Player));
    return game;
}

void add_player(Game *game, int player_socket)
{
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        //find free spot in players array
        if (game->players[i].player_socket == 0)
        {
            // MODIFY COORDS
            Paddle *paddle = malloc(sizeof(*paddle));
            paddle->x_coord = 10;
            paddle->y_coord = 10;
            
            Player *player = malloc(sizeof(*player));
            player->player_socket = player_socket;
            player->paddle_type = LEFT + i;
            player->score = 0;
            player->paddle = paddle;
            
            game->players[i] = *player;
            game->number_players++;
            break;
        }
    }
}

void disconnect_player(Game *game, int sd)
{
    // get his details and print
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    getpeername(sd, (struct sockaddr *) &cli_addr, &clilen);
    printf("Host disconnected, port %d \n", ntohs(cli_addr.sin_port));
    
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (game->players[i].player_socket == sd)
        {
            // free paddle and player
            Player player = game->players[i];
            free(player.paddle);
            free(&player);
            
            game->number_players--;
            break;
        }
    }
    
    // close the socket
    close(sd);
}

void pong(int port_num)
{
    int server_socket = start_server(port_num);
    Game *game = init_game(server_socket, port_num);
    
    // zero out all client_sockets
    int client_sockets[MAX_PLAYERS] = {0};
    
    while(game->number_players < MAX_PLAYERS)
    {
        // set of socket descriptors
        fd_set readfds;
        // clear the socket set
        FD_ZERO(&readfds);
        
        // wait for players to join game
        if (wait_for_connection(server_socket, MAX_PLAYERS, &readfds, client_sockets) == 1)
        {
            int player_socket = add_connection(server_socket, client_sockets, MAX_PLAYERS);
            add_player(game, player_socket);
        }
        else
        {
            int sd;
            // read from socket into buffer
            char buffer[256] = {0};
            
            long valread = handle_connection(&readfds, client_sockets, MAX_PLAYERS, &sd, buffer);
            // somebody disconnected
            if (valread == 0)
            {
                disconnect_player(game, sd);
            }
            else
            {
                // use valread to update
                
            }
        }
        
        // close the server when no more clients
        if (game->number_players == 0)
        {
            close(server_socket);
            break;
        }
    }
}