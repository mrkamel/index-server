
#include "stdin.h"

#include <stdio.h>

int stdin_readline(string* str) {
 char c;

 while((c = getchar()) != EOF) {
  if(c == '\n')
   return str->used;

  string_concat(str, c);
 }

 return 0;
}

