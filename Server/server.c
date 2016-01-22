//
//  server.c
//  Multiplayer Pong
//
//

#include "server.h"

typedef struct game
{
    int server_socket;
    int server_port;
    int number_players;
    struct player *players[MAX_PLAYERS];
    
    
    
    // may not need these
    int max_score;
    int max_player;
} Game;

void start_game()
{
    
}

void end_game()
{
    
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void start_server(int port_num)
{
    // client sockets initialized to 0
    int client_sockets[MAX_PLAYERS], i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        client_sockets[i] = 0;
    }
    
    // create server socket
    int master_socket;
    master_socket = socket(AF_INET, SOCK_STREAM, 0); // address domain, socket type, protocol
    if (master_socket < 0)
    {
        error("Error opening socket");
    }
    
    // set up server address and port
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    ///CHANGE PORTS FOR GAMES
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = INADDR_ANY; // IP address of host
    
    // bind socket to server address + serverPort
    if (bind(master_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        error("Error binding socket");
    }
    
    // listen
    listen(master_socket, 5); // listen on socket for at most 5 backlog queue
    
    // accept incoming connections, need client address
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    
    // set of socket descriptors
    fd_set readfds;
    int max_sd, sd;
    
    // read from socket into buffer
    char buffer[256];
    bzero(buffer, 256);
    
    int counter = 0;
    while(counter < MAX_PLAYERS)
    {
        // clear the socket set
        FD_ZERO(&readfds);
        
        // add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
        
        // add child sockets to set
        for (i = 0; i < MAX_PLAYERS; i++)
        {
            // socket descriptor
            sd = client_sockets[i];
            
            // if valid socket descriptor then add to read list
            if (sd > 0)
            {
                FD_SET(sd, &readfds);
            }
            
            // highest file descriptor number, need it for the select function
            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }
        
        // wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0)
        {
            printf("select error");
        }
        
        // if something happened on the master socket, then it's an incoming connection
        int new_socket;
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &cli_addr, &clilen)) < 0)
            {
                perror("accept error");
                exit(EXIT_FAILURE);
            }
            
            // inform user of socket number - used in send and receive commands
            counter++;
            printf("New connection, socket fd is %d, port : %d \n", new_socket, ntohs(cli_addr.sin_port));
            
            // add new socket to array of sockets
            for (i = 0; i < MAX_PLAYERS; i++)
            {
                // if position is empty
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    
                    break;
                }
            }
        }
        
        // some IO operation on some other socket
        for (i = 0; i < MAX_PLAYERS; i++)
        {
            sd = client_sockets[i];
            
            if (FD_ISSET(sd, &readfds))
            {
                // check if it was for closing, and also read the incoming message
                long valread = read(sd, buffer, 255);
                if (valread == 0)
                {
                    // somebody disconnected, get his details and print
                    getpeername(sd, (struct sockaddr *) &cli_addr, &clilen);
                    printf("Host disconnected, port %d \n", ntohs(cli_addr.sin_port));
                    counter--;
                    
                    // close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_sockets[i] = 0;
                }
                
                // CHANGE TO OUTPUTTING NEW LOCATIONS OF PADDLES AND BALLS
                // echo back the message that came in
                else
                {
                    // set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }
}

void closeSocket(int socket, struct socket_manager *manager)
{
    close(socket);
}