#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "socket_common.h"


const unsigned int BUFFER_SIZE = 1024;


struct IncomingConnection* acceptIncomingConnection(int socket_fd)
{
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);

    int client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_address, &client_address_size);
    die_on_failure(client_socket_fd < 0, "failed to accept connection");

    struct IncomingConnection* result = malloc(sizeof(struct IncomingConnection));
    result->accepted_socket_fd = client_socket_fd;
    result->address = client_address;
    result->accepted_successfully = client_socket_fd > 0;
    result->error_code = result->accepted_successfully ? 0 : client_socket_fd;
    
    return result;
}

void processConnection(int socket_fd)
{
    char buffer[BUFFER_SIZE];

    while (1)
    {
        long bytes_received = recv(socket_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0)
        {
            perror("Failed to receive response");
            break;
        }

        if (bytes_received > 0)
        {
            buffer[bytes_received] = 0;
            printf("Received %ld bytes: %s\n", bytes_received, buffer);
        }

        if (bytes_received == 0)
        {
            printf("Connection was closed by the client\n");
            break;
        }
    }
}