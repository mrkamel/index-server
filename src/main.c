
#include "std/socket.h"

#include "request.h"
#include "stdin.h"
#include "index.h"

#include <stdio.h>

void server(int port) {
 int s;

 s = socket_socket();
 
 socket_bind(s, port);
 
 socket_listen(s, 500);

 request_handle_requests(s);

 close(s);
}

void create_index() {
 int count = 0;
 string str;

 string_init(&str);

 index_init();

 while(stdin_readline(&str)) {
  index_add(&str);

  string_empty(&str); 
 
  count++;

  if(count % 100 == 0)
   printf("%i\n", count);
 }

 index_finalize();

 string_delete(&str); 
}

int main(int argc, char** argv) {
 if(argc < 2) {
  printf("you have to specify a port\n");

  return 0;
 }

 create_index();

 server(atoi(argv[1]));

 return 0;
}

