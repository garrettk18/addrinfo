#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([addrinfo], [0.1.1], [garrett@garrettspace.net])
AC_CONFIG_SRCDIR([src/config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(Ws2_32, WSAStartup, , , -lAdvapi32 -lMswsock)

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h sys/socket.h unistd.h getopt.h winsock2.h ws2tcpip.h windows.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile src/Makefile])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_OUTPUT
