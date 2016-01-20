//
//  server.c
//  Multiplayer Pong
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//const int serverPort = 9000;

void server()
{
    // open socket
    int sockfd;
    sockfd = socket(AF_INET6, SOCK_STREAM, 0); // address domain, socket type, protocol
    if (sockfd < 0)
        perror("Error opening socket");
    
    // set up server address and port
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET6;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY; // IP address of host aka IP address of my machine
    
    // bind socket to server address + serverPort
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        perror("Error binding socket");
    
    // listen
    listen(sockfd, 5); // listen on socket for at most 5 backlog queue
    
    // accept incoming connection, need client address
    struct sockaddr_in cli_addr;

    int newsocketfd = accept(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
    while (newsocketfd > 0)
    {
        // read from socket into buffer
        char buffer[256];
        bzero(buffer, 256);
        int n = read(newsocketfd, buffer, 255);
        if (n < 0)
            perror("Error in reading");
        
        close(newsocketfd);
        newsocketfd = accept(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
    }
}

int main(int argc, char *argv[])
{
    server();
    return 0;
}

//struct sockaddr_in
//{
//    short   sin_family; /* must be AF_INET */
//    u_short sin_port;
//    struct  in_addr sin_addr;
//    char    sin_zero[8]; /* Not used, must be zero */
//};