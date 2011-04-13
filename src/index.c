
#include "index.h"

#include <stdlib.h>
#include <stdio.h>

array descriptions_g;
hash keywords_g;

void index_init() {
 array_init(&descriptions_g);
 hash_init(&keywords_g);
}

void index_add_description(string* desc) {
 array_push(&descriptions_g, (int)desc);
}

void index_finalize() {
 int i, count = 0, full = 0;

 for(i = 0; i < keywords_g.size; i++) {
  if(keywords_g.keys[i]) {
   array_finalize(keywords_g.values[i]);
   
   count++;

   full += keywords_g.values[i]->used;
  }
 }

 printf("%i keywords\n", count);
 printf("%i indices\n", full);
}

void index_add_keyword(string* keyword) {
 array* identifiers;
 int index;
 
 index = hash_get(&keywords_g, keyword);

 if(index == -1) { /* identifier-array for keyword not present => create */
  identifiers = (array*)malloc(sizeof(array));

  array_init(identifiers);

  hash_put(&keywords_g, keyword, identifiers);
 } else { /* identifier-array for keyword exists => keyword-pointer no longer needed => free */
  identifiers = keywords_g.values[index];

  string_delete(keyword), free(keyword);
 }

 array_push(identifiers, descriptions_g.used);
}

void index_add_keywords(string* keyword_string) {
 array keywords;
 int i;

 array_init(&keywords);

 string_split(keyword_string, &keywords, ',');

 for(i = 0; i < keywords.used; i++)
  index_add_keyword((string*)keywords.data[i]);

 /* keywords.data[x] are maybe in use => no string_array_delete */

 array_delete(&keywords);
}

/* DESCRIPTION \t KEYWORDS */

void index_add(string* line) {
 array fields;

 array_init(&fields);

 string_split(line, &fields, '\t');

 index_add_keywords((string*)fields.data[1]);

 index_add_description((string*)fields.data[0]);

 /* fields.data[0] is in use => no array_delete_all, only free fields.data[1] */

 string_delete((string*)fields.data[1]), free((void*)fields.data[1]);

 array_delete(&fields);
}

