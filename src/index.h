
#ifndef INDEX_H
#define INDEX_H

#include "std/string.h"
#include "std/hash.h"

extern hash keywords_g;
extern array descriptions_g;

void index_init();
void index_add(string*);
void index_finalize();

#endif

