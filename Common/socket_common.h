#ifndef COMMON_LIBRARY_H
#define COMMON_LIBRARY_H

#include <netinet/in.h>
#include <stdbool.h>


extern void die_on_failure(bool res, const char* msg);

extern void create_inet_address(const char* ip, unsigned int port, struct sockaddr_in* address);

#endif //COMMON_LIBRARY_H
