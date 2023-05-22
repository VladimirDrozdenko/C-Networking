#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket_common.h"


const unsigned int local_port = 2000;
const int connection_queue_len = 10;
const unsigned int BUFFER_SIZE = 1024;


int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    die_on_failure(socket_fd < 0, "create socket failed");

    struct sockaddr_in local_address;
    create_inet_address(0, local_port, &local_address);

    die_on_failure(bind(socket_fd, (struct sockaddr*) &local_address, sizeof(local_address)) != 0, "bind socket to address failed");

    die_on_failure(listen(socket_fd, connection_queue_len) != 0, "failed to setup listener");

    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);

    int client_socket_fd = accept(socket_fd, (struct sockaddr*) &client_address, &client_address_size);
    die_on_failure(client_socket_fd < 0, "failed to accept connection");

    char buffer[BUFFER_SIZE];

    while (1)
    {
        long bytes_received = recv(client_socket_fd, buffer, BUFFER_SIZE, 0);
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
    

    close(client_socket_fd);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return EXIT_SUCCESS;
}
