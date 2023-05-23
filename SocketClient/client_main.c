#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "socket_common.h"

const char* ip = "127.0.0.1";
const unsigned int port = 2000; //80;

//const unsigned int BUFFER_SIZE = 2048;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    die_on_failure(socket_fd < 0, "create socket failed");

    struct sockaddr_in address;
    create_inet_address(ip, port, &address);

    printf("Attempting to connect to %s:%d...", ip, port);
    fflush(stdout);

    int res = connect(socket_fd, (const struct sockaddr*)&address, sizeof(address));
    die_on_failure(res != 0, "connect failed");

    printf("[Connected]\n");

    printf("Type your message ('exit' to exist the client)\n\n");

    char* buffer = 0;
    size_t buff_capacity = 0;

    while (1)
    {
        ssize_t chars_received = getline(&buffer, &buff_capacity, stdin);
        if (chars_received <= 0)
        {
            continue;
        }

        buffer[chars_received-1] = 0;

        if (0 == strcmp(buffer, "exit"))
        {
            break;
        }

        long bytes_sent = send(socket_fd, buffer, strlen(buffer), 0);
        if (bytes_sent < 0)
        {
            perror("failed to send request");
            break;
        }
    }

    // long bytes_received = recv(socket_fd, &buffer, BUFFER_SIZE, 0);
    // if (bytes_received < 0)
    // {
    //     fprintf(stderr, "Failed to receive response. Error: %s\n", strerror(errno));
    //     close(socket_fd);
    //     exit(EXIT_FAILURE);
    // }

    // printf("[[Received %ld bytes]]\n", bytes_received);
    // printf("%s\n", buffer);

    close(socket_fd);
    return EXIT_SUCCESS;
}
