//
//  client.c
//  Multiplayer Pong
//
//

#include "client.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void start_client(char *server_name[], int port_num)
{
    // create client socket
    int master_socket;
    master_socket = socket(AF_INET, SOCK_STREAM, 0); // address domain, socket type, protocol
    if (master_socket < 0)
    {
        error("ERROR opening socket");
    }
    
    // set up server address and port
    struct sockaddr_in serv_addr;
    struct hostent *server;
    server = gethostbyname(*server_name);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_num);
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    
    // connect
    if (connect(master_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
    
    while (1)
    {
        // enter a message
        printf("Please enter the message: ");
        char buffer[256];
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        
        if (strcmp(buffer, "logout\n") == 0)
        {
            printf("Bye bye\n");
            break;
        }
        
        long n;
        // write to socket
        n = write(master_socket, buffer, strlen(buffer));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
        bzero(buffer, 256);
        
        // read from socket
        n = read(master_socket, buffer, 255);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        
        printf("%s\n", buffer);
    }
    
    close(master_socket);
}
