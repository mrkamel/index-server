
#ifndef STRING_H
#define STRING_H

#include "shared.h"
#include "array.h"

typedef struct {
 char* data;
 int size, used;
} string;

void string_init(string*);
void string_concat_string(string*, char*);
void string_concat(string*, char);
uint string_hash(string*);
void string_split(string*, array*, char);
void string_delete(string*);
void string_array_delete(array*);
void string_empty(string*);

#endif

