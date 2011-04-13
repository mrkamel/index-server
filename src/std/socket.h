
#ifndef SOCKET_H
#define SOCKET_H

#include "string.h"

int socket_socket();
void socket_bind(int, ushort);
void socket_listen(int, int);
int socket_accept(int);
int socket_readline(int, string*);
int socket_write(int, char*);
void socket_set_timeout(int, int, int);

#endif

