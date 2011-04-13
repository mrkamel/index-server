
#ifndef HASH_H
#define HASH_H

#include "string.h"
#include "array.h"

typedef struct {
 string** keys;
 array** values;
 int used, size;
} hash;

void hash_init(hash*);
int hash_put(hash*, string*, array*);
int hash_get(hash*, string*);

#endif

