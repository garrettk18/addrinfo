#ifdef _WIN32
    #pragma comment (lib, "Ws2_32.lib")
    #pragma comment (lib, "Mswsock.lib")
    #pragma comment (lib, "AdvApi32.lib")
#endif
#include "addrinfo.h"

int main(int argc, char *argv[])
{
    #ifndef _WIN32
        opterr = 0; //Suppress builtin getopt diagnostics
        int opt = 0;
    #endif
    int ipv4_only = 0;
    int ipv6_only = 0;
    if (argc == 1) {
        usage();
        exit(EXIT_FAILURE);
    } //if
    const char *optstring = "46";
    #ifdef _WIN32
        int i = 0;
        for (i = 1; i < argc; i++) {
            if (!strcmp("-4", argv[i])) {
                ipv4_only = 1;
                ipv6_only = 0;
            } //if
            else if (!strcmp("-6", argv[i])) {
                ipv6_only = 1;
                ipv4_only = 0;
            } //else if
            else {
                //The argument is a hostname. Break out of the loop and preserve the value of i for later.
                break;
            } //else
        } //for
    WSADATA wsaData;
    int iResult;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(EXIT_FAILURE);
    } //if
    #else
        while ((opt = getopt(argc, argv, optstring)) != -1) {
            switch(opt) {
                case '4':
                    ipv4_only = 1;
                    ipv6_only = 0;
                break;
                case '6':
                    ipv6_only = 1;
                    ipv4_only = 0;
                break;
                case '?':
                    fprintf(stderr,"Unrecognized option -%c\n", optopt);
                    usage();
                    exit(EXIT_FAILURE);
                break;
                default:
                    usage();
                    exit(EXIT_FAILURE);
            } //switch
        } //while
        if (optind >= argc) {
            fprintf(stderr, "Missing hostname argument.\n");
            usage();
            exit(EXIT_FAILURE);
        } //if
    #endif
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        if (!ipv4_only && !ipv6_only) {
            hints.ai_family = 0;
        } //if
        else if (ipv4_only && !ipv6_only) {
            hints.ai_family = AF_INET;
        } //if
        else {
            hints.ai_family = AF_INET6;
        } //else
        hints.ai_flags = AI_CANONNAME;
        struct addrinfo *res = NULL;
        int gaistatus = getaddrinfo(argv[argc - 1], NULL, &hints, &res);
        if (gaistatus) {
            fprintf(stderr, "getaddrinfo() Error: %s\n", gai_strerror(gaistatus));
            exit(EXIT_FAILURE);
        } //if
    
    for(struct addrinfo *i = res; i != NULL; i = i->ai_next) {
        parseaddrinfo(i);
    } //for
    freeaddrinfo(res);
    return 0;
} //main

//Logic for printing struct addrinfo members.

void parseaddrinfo(const struct addrinfo *ai)
{
    char ipbuf[INET6_ADDRSTRLEN];
    char *ipstr = NULL;
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)ai->ai_addr;
    struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)ai->ai_addr;
    printf("Socket family: ");
    switch(ai->ai_family) {
      case AF_INET: 
        ipstr = (char *)inet_ntop(ai->ai_family, &(ipv4->sin_addr), ipbuf, INET_ADDRSTRLEN);
        printf("IPv4");
      break;
      case AF_INET6:
        ipstr = (char *)inet_ntop(ai->ai_family, &(ipv6->sin6_addr), ipbuf, INET6_ADDRSTRLEN);
        printf("IPv6");
      break;
      case AF_UNSPEC:
        printf("unspecified");
      break;
      default:
        printf("unknown");
    } //switch
    putchar('\n');
    printf("Socket type: ");
    switch(ai->ai_socktype) {
      case SOCK_STREAM:
        printf("stream");
      break;
      case SOCK_DGRAM:
        printf("datagram");
      break;
      case SOCK_SEQPACKET:
        printf("seqpacket");
      break;
      case SOCK_RAW:
        printf("raw");
      break;
      default:
        printf("unknown");
    } //switch
    putchar('\n');
    if (!ipstr) {
      perror("inet_ntop");
      return;
    } //if
    printf("IP address: %s\n", ipstr);
    printf("Address structure length in bytes: %zu\n", ai->ai_addrlen);
    printf("Canonical name: %s\n", ai->ai_canonname);
} //parseaddrinfo

void usage(void)
{
    printf("Usage: %s [-46] <hostname>\n", "addrinfo.exe");
    printf("-4: IPv4-only\n");
    printf("-6: IPv6-only\n");
} //usage
