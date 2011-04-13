
#ifndef QUERY_H
#define QUERY_H

#include "and_combination.h"

typedef array query;

void query_init(query*);
void query_prepare(query*);
void query_add(query*, string*, string*);
inline int query_get_next(query*);
void query_delete(query*);

#endif

