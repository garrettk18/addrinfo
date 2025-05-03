#ifndef _ADDRINFO_H
  #define _ADDRINFO_H
  #define _GNU_SOURCE
  #include <errno.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netdb.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>
//#include <getopt.h>

  void parseaddrinfo(const struct addrinfo *ai);
  void usage(void);
#endif //_ADDRINFO_H

