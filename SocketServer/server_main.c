#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket_common.h"
#include "utils.h"


const unsigned int local_port = 2000;
const int connection_queue_len = 10;


int main()
{
    printf("PID: %d\n", getpid());

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    die_on_failure(socket_fd < 0, "create socket failed");

    struct sockaddr_in local_address;
    create_inet_address(0, local_port, &local_address);

    die_on_failure(bind(socket_fd, (struct sockaddr*) &local_address, sizeof(local_address)) != 0, "bind socket to address failed");

    die_on_failure(listen(socket_fd, connection_queue_len) != 0, "failed to setup listener");

    printf("Service is listening...\n");

    struct IncomingConnection* connection = acceptIncomingConnection(socket_fd);

    processConnection(connection->accepted_socket_fd);

    close(connection->accepted_socket_fd);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);

    return EXIT_SUCCESS;
}
