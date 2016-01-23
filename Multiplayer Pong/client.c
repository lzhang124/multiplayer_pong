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

int start_client(char *server_name[], int port_num)
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
    bcopy((char *) server->h_addr,
          (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    
    // connect
    if (connect(master_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
    
    return master_socket;
}

void write_string(int master_socket, char * buffer)
{
    write(master_socket, buffer, sizeof(*buffer));
    free(buffer);
}

char *read_string(int master_socket)
{
    char *buffer = malloc(sizeof(*buffer) * 8);
    long n = read(master_socket, buffer, sizeof(*buffer));
    if (n != -1)
    {
        return buffer;
    }
    return NULL;
}

void write_number(int master_socket, int number)
{
    write(master_socket, &number, sizeof(number));
}

int read_number(int master_socket)
{
    int number;
    long n = read(master_socket, &number, sizeof(number));
    if (n != -1)
    {
        return number;
    }
    return -1;
}

void end_connection(int master_socket)
{
    close(master_socket);
}
