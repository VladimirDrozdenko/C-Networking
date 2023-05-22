#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


struct IncomingConnection
{
    int accepted_socket_fd;
    struct sockaddr_in address;
    int error_code;
    int accepted_successfully;
};

extern struct IncomingConnection* acceptIncomingConnection(int socket_fd);
extern void processConnection(int socket_fd);

#endif //__UTILS_H__
