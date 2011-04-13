
#include "hash.h"

#include <string.h>

#define HASH_INITIAL_SIZE 20
#define HASH_LOAD 0.75

void hash_init(hash* h) {
 h->keys = 0;
 h->values = 0;
 h->used = 0;
 h->size = 0;
}

uint hash_index(hash* h, string* key) {
 return string_hash(key) % h->size;
}

void hash_initial(hash* h, int size) {
 h->size = (!size)?HASH_INITIAL_SIZE:size;

 h->keys = (string**)realloc(h->keys, h->size * sizeof(string*));
 h->values = (array**)realloc(h->values, h->size * sizeof(array*));

 memset(h->keys, 0, h->size * sizeof(string*));
}

void hash_put_nocheck(hash* h, string* key, array* value) {
 int index = hash_find_free_slot(h, key);

 h->keys[index] = key;
 h->values[index] = value;

 h->used++;
}

void hash_swap(hash* dest, hash* source) {
 free(dest->keys);
 free(dest->values);

 dest->keys = source->keys;
 dest->values = source->values;

 dest->size = source->size;
 dest->used = source->used;
}

void hash_copy(hash* dest, hash* source) {
 int i;

 for(i = 0; i < source->size; i++) {
  if(source->keys[i])
   hash_put_nocheck(dest, source->keys[i], source->values[i]);
 }

 hash_swap(source, dest);
}

void hash_grow(hash* h) {
 if(!h->size)
  hash_initial(h, 0);
 else if((double)h->used / (double)h->size >= HASH_LOAD) {
  hash copy;

  hash_init(&copy);

  hash_initial(&copy, h->size * 2);

  hash_copy(&copy, h);
 }
}

int hash_find_free_slot(hash* h, string* key) {
 uint index, i;
 
 index = hash_index(h, key);

 if(!h->keys[index])
  return index;

 for(i = index + 1; i % h->size != index; i++) {
  if(!h->keys[i % h->size])
   return i % h->size;
 }

 return -1;
}

int hash_get(hash* h, string* key) {
 uint index, i;

 hash_grow(h);

 index = hash_index(h, key);

 if(!h->keys[index])
  return -1;

 if(!strcmp(h->keys[index]->data, key->data))
  return index;

 for(i = index + 1; i % h->size != index; i++) {
  if(!h->keys[i % h->size])
   return -1;

  if(!strcmp(h->keys[i % h->size]->data, key->data))
   return i % h->size;
 }

 return -1;
}

int hash_put(hash* h, string* key, array* value) {
 hash_grow(h);

 if(hash_get(h, key) == -1) {
  hash_put_nocheck(h, key, value);

  return 1;
 }

 return 0;
}

void hash_delete(hash* h) {
 int i;

 for(i = 0; i < h->size; i++) {
  if(h->keys[i]) {
   string_delete(h->keys[i]);
   array_delete(h->values[i]);

   free(h->keys[i]);
   free(h->values[i]);
  }
 }

 free(h->keys);
 free(h->values);
}

