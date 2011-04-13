
#include "query.h"
#include "def.h"

#include <stdlib.h>

void query_init(query* q) {
 array_init(q);
}

void query_delete(query* q) {
 int i;

 /* delete and_combination's data */

 for(i = 0; i < q->used; i++)
  and_combination_delete((and_combination*)q->data[i]);

 /* delete pointer on and_combination's */

 array_delete_all(q);
}

void query_prepare(query* q) {
 int i;

 for(i = 0; i < q->used; i++) {
  and_combination_prepare((and_combination*)q->data[i]);
  and_combination_get_next((and_combination*)q->data[i]);
 }
}

inline int query_get_min(query* q) {
 int index = 0, i;

 if(!q->used)
  return DEF_INVALID;

 for(i = 1; i < q->used; i++) {
  if(((and_combination*)q->data[i])->data < ((and_combination*)q->data[index])->data)
   index = i;
 }

 return index;
}

inline int query_get_next(query* q) {
 int index, res;
 
 index = query_get_min(q);

 if(index == DEF_INVALID)
  return DEF_INVALID;

 res = ((and_combination*)q->data[index])->data;

 and_combination_get_next((and_combination*)q->data[index]);

 return res;
}

void query_add(query* q, string* ands, string* nots) {
 and_combination* ac;
 array words;
 int i;
 
 ac = (and_combination*)malloc(sizeof(and_combination));

 and_combination_init(ac);

 array_init(&words);

 string_split(ands, &words, ',');
 
 for(i = 0; i < words.used; i++) {
  if(!and_combination_add_and(ac, (string*)words.data[i])) { /* word not found => abort and_combination */
   and_combination_delete(ac);
   
   string_array_delete(&words);

   free(ac);

   return;
  }
 }

 string_array_delete(&words);

 array_init(&words);

 string_split(nots, &words, ',');

 for(i = 0; i < words.used; i++)
  and_combination_add_not(ac, (string*)words.data[i]);

 string_array_delete(&words);

 array_push(q, (int)ac); 
}

