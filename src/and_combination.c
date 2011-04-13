
#include "and_combination.h"
#include "index.h"
#include "def.h"

void and_combination_delete(and_combination* ac) {
 /* don't delete real data, only pointers */
 array_delete(&ac->ands);
 array_delete(&ac->nots);
}

void and_combination_init(and_combination* ac) {
 array_init(&ac->ands);
 array_init(&ac->nots);

 ac->current = 0;
}

int and_combination_add(array* a, string* str) {
 int i = hash_get(&keywords_g, str);

 if(i == -1)
  return 0;

 array_push(a, (int)keywords_g.values[i]);

 return 1;
}

int and_combination_add_and(and_combination* ac, string* str) {
 return and_combination_add(&ac->ands, str);
}

int and_combination_add_not(and_combination* ac, string* str) {
 return and_combination_add(&ac->nots, str);
}

int less_array_size(int a, int b) {
 return ((array*)a)->used < ((array*)b)->used;
}

void and_combination_prepare(and_combination* ac) {
 array_sort(&ac->ands, less_array_size);
 array_sort(&ac->nots, less_array_size);
}

inline int and_combination_check_next(and_combination* ac) {
 int i, c;

 if(ac->current >= ((array*)ac->ands.data[0])->used)
  return ac->data = DEF_INVALID;

 c = ((array*)ac->ands.data[0])->data[ac->current];

 for(i = 1; i < ac->ands.used; i++) {
  if(array_binary_search((array*)ac->ands.data[i], c) == -1) {
   ac->current++;

   return ac->data = -2;
  }
 }
 
 for(i = 0; i < ac->nots.used; i++) {
  if(array_binary_search((array*)ac->nots.data[i], c) != -1) {
   ac->current++;

   return ac->data = -2;
  }
 }
 
 ac->current++;

 return ac->data = c;
}

inline int and_combination_get_next(and_combination* ac) {
 while(and_combination_check_next(ac) == -2);
 
 return ac->data;
}

