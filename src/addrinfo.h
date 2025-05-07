#ifndef _ADDRINFO_H
    #define _ADDRINFO_H
    #define _GNU_SOURCE
    #include <errno.h>
    #include <string.h>
    #ifndef _WIN32
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netdb.h>
        #include <unistd.h>
        #include <arpa/inet.h>
        #include <netinet/in.h>
    #else
        #include <windows.h>
        #include <winsock2.h>
        #include <ws2tcpip.h>
        #pragma comment (lib, "Ws2_32.lib")
        #pragma comment (lib, "Mswsock.lib")
        #pragma comment (lib, "AdvApi32.lib")
    #endif
    #include <stdio.h>
    #include <stdlib.h>
    //#include <getopt.h>

void parseaddrinfo(const struct addrinfo* ai);
void usage(void);
#endif //_ADDRINFO_H

