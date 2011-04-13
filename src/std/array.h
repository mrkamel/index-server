
#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
 int* data;
 int size, used;
} array;

void array_init(array*);
void array_push(array*, int);
void array_delete(array*);
void array_delete_all(array*);
void array_sort(array*,int (*)(int, int));
inline int array_binary_search(array*, int);
void array_finalize(array*);

#endif

