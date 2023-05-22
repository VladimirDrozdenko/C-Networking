#ifndef COMMON_LIBRARY_H
#define COMMON_LIBRARY_H

#include <netinet/in.h>

extern void die_on_failure(int res, const char* msg);

extern void create_inet_address(const char* ip, unsigned int port, struct sockaddr_in* address);

#endif //COMMON_LIBRARY_H
