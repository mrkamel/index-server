
#ifndef AND_COMBINATION_H
#define AND_COMBINATION_H

#include "std/string.h"

typedef struct {
 array ands;
 array nots;
 int current;
 int data;
} and_combination;

void and_combination_init(and_combination*);
int and_combination_add_and(and_combination*, string*);
int and_combination_add_not(and_combination*, string*);
void and_combination_prepare(and_combination*);
inline int and_combination_get_next(and_combination*);
void and_combination_delete(and_combination*);

#endif

