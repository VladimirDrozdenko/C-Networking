#include "socket_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void die_on_failure(int res, const char* msg)
{
    if (res)
    {
        perror(msg);
        exit(errno);
    }
}


void create_inet_address(const char* ip, unsigned int port, struct sockaddr_in* address)
{
    memset(address, 0, sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (ip == 0 || *ip == 0)
    {
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }
}