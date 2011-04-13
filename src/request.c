
#include "std/string.h"

#include "request.h"
#include "query.h"
#include "index.h"
#include "def.h"

#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>

void request_send_result(int sock, query* q, int a, int b) {
 int current, res = 0, last = -1;
 char buffer[32];

 while((current = query_get_next(q)) != DEF_INVALID) {
  if(last != current) { 
   if(res >= a && res <= b) { /* current result within interval? */
    socket_write(sock, ((string*)descriptions_g.data[current])->data);
    socket_write(sock, "\n");
   }

   res++;
  }

  last = current;
 }

 snprintf(buffer, 31, "%i\n", res);
 
 socket_write(sock, buffer);
}

int request_read_query(int sock, query* q) {
 string ands, nots;

 string_init(&ands), string_init(&nots);
 
 while(1) { /* get query */
  if(socket_readline(sock, &ands) == -1 || socket_readline(sock, &nots) == -1) {
   string_delete(&ands), string_delete(&nots);

   return 0;
  }
   
  if(!ands.used && !nots.used)
   break;

  query_add(q, &ands, &nots);

  string_empty(&ands), string_empty(&nots);
 }

 string_delete(&ands), string_delete(&nots);

 return 1;
}

int request_read_integer(int sock, int* i) {
 string str;

 string_init(&str);

 if(socket_readline(sock, &str) == -1 || !str.used) {
  string_delete(&str);

  return 0;
 }

 *i = atoi(str.data);

 string_delete(&str);

 return 1;
}

void request_answer(int sock) {
 int start, end;
 struct timeval t1, t2;
 query q;

 gettimeofday(&t1, 0);

 query_init(&q);

 socket_set_timeout(sock, 5, 5);

 /* read query, read interval start, read interval end */

 if(!request_read_query(sock, &q) || !request_read_integer(sock, &start) || !request_read_integer(sock, &end)) {
  query_delete(&q);

  close(sock);

  return;
 }

 query_prepare(&q);

 request_send_result(sock, &q, start, end);

 query_delete(&q);

 close(sock);

 gettimeofday(&t2, 0);

 /* printf("%i milliseconds\n", ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec) / 1000); */

 return;
}

void request_handle_requests(int sock) {
 while(1)
  request_answer(socket_accept(sock));
}

