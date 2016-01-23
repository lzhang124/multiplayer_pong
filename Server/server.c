//
//  server.c
//  Multiplayer Pong
//
//

#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int add_connection(int master_socket, int client_sockets[], int max_connections)
{
    // accept incoming connections, need client address
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    
    int new_socket;
    if ((new_socket = accept(master_socket, (struct sockaddr *) &cli_addr, &clilen)) < 0)
    {
        perror("accept error");
        exit(EXIT_FAILURE);
    }
    
    // inform user of socket number - used in send and receive commands
    printf("New client, socket fd is %d, port : %d \n", new_socket, ntohs(cli_addr.sin_port));
    
    // add new socket to array of clients
    int i;
    for (i = 0; i < max_connections; i++)
    {
        // if position is empty
        if (*(client_sockets+i) == 0)
        {
            printf("Adding to list of clients as %d\n", i);
            *(client_sockets+i) = new_socket;
            break;
        }
    }
    return new_socket;
}

long handle_connection(fd_set *readfds, int client_sockets[], int max_connections, int *sd, char buffer[])
{
    int i;
    for (i = 0; i < max_connections; i++)
    {
        *sd = *(client_sockets+i);
        
        if (FD_ISSET(*sd, readfds))
        {
            // return the incoming message
            return read(*sd, buffer, 255);
        }
    }
    return -1;
}

int wait_for_connection(int master_socket, int max_connections, fd_set *readfds, int client_sockets[])
{
    int max_sd, sd;
    
    // add server socket to set
    FD_SET(master_socket, readfds);
    max_sd = master_socket;
    
    int i;
    // add child sockets to set
    for (i = 0; i < max_connections; i++)
    {
        // socket descriptor
        sd = *(client_sockets+i);
        
        // if valid socket descriptor then add to read list
        if (sd > 0)
        {
            FD_SET(sd, readfds);
        }
        
        // highest file descriptor number, need it for the select function
        if (sd > max_sd)
        {
            max_sd = sd;
        }
    }
    
    // wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
    int activity = select(max_sd + 1, readfds, NULL, NULL, NULL);
    if (activity < 0)
    {
        printf("select error");
    }
    
    // if something happened on the master socket, then it's an incoming connection
    if (FD_ISSET(master_socket, readfds))
    {
        return 1;
    }
    // some IO operation on some other socket
    return 0;
}

int start_server(int port_num)
{
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
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = INADDR_ANY; // IP address of host
    
    // bind socket to server address + serverPort
    if (bind(master_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        error("Error binding socket");
    }
    
    // listen
    listen(master_socket, 5); // listen on socket for at most 5 backlog queue
    
    return master_socket;
}
