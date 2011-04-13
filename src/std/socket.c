
#include "socket.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include <string.h>

#include <time.h>

int socket_socket() {
 return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void socket_bind(int s, ushort port) {
 struct sockaddr_in sockaddr;

 memset(&sockaddr, 0, sizeof(sockaddr));

 sockaddr.sin_family = AF_INET;
 //sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 sockaddr.sin_port = htons(port);

 bind(s, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
}

void socket_listen(int s, int max) {
 listen(s, max);
}

int socket_accept(int s) {
 struct sockaddr_in sockaddr;
 socklen_t len;

 len = sizeof(sockaddr);

 return accept(s, (struct sockaddr*)&sockaddr, &len);
}

void socket_set_timeout(int s, int sec_read, int sec_write) {
 struct timeval t;

 t.tv_sec = sec_read;
 t.tv_usec = 0;

 setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t));

 t.tv_sec = sec_write;

 setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &t, sizeof(t));
}

int socket_readline(int s, string* str) {
 int len;
 char c;

 while((len = recv(s, &c, 1, 0)) != 0 && len != -1) {
  if(c == '\n')
   return str->used;

  string_concat(str, c);
 }

 return -1;
}

int socket_write(int s, char* str) {
 return send(s, str, strlen(str), MSG_NOSIGNAL);
}


