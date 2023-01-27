#include "addrinfo.h"

int main(int argc, char *argv[])
{
  if (argc == 2) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    //hints.ai_family = AF_INET6;
    hints.ai_flags = AI_CANONNAME;
    struct addrinfo *res = NULL;
    int gaistatus = getaddrinfo(argv[1], NULL, &hints, &res);
    if (gaistatus) {
      fprintf(stderr, "getaddrinfo() Error: %s\n", gai_strerror(gaistatus));
      exit(EXIT_FAILURE);
    } //if
    
    for(struct addrinfo *i = res; i != NULL; i = i->ai_next) {
      parseaddrinfo(i);
    } //for
    freeaddrinfo(res);
  } //if
  else {
    usage();
  } //else, wrong number of args
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
    break;
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
    case SOCK_RAW:
      printf("raw");
    break;
    default:
      printf("unknown");
    break;
  } //switch
  putchar('\n');
  if (!ipstr) {
    perror("inet_ntop");
    return;
  } //if
  printf("IP address: %s\n", ipstr);
  printf("Address structure length in bytes: %d\n", ai->ai_addrlen);
  printf("Canonical name: %s\n", ai->ai_canonname);
} //parseaddrinfo

void usage(void)
{
  printf("Usage: %s <hostname>\n", program_invocation_name);
} //usage
