
#include "array.h"

#define ARRAY_GROW 20

void array_grow(array* a) {
 if(a->used >= a->size) {
  a->data = (int*)realloc(a->data, (a->size + ARRAY_GROW) * sizeof(int));

  a->size += ARRAY_GROW;
 }
}

void array_init(array* a) {
 a->data = 0;
 a->size = 0;
 a->used = 0;
}

void array_push(array* a, int i) {
 array_grow(a);

 a->data[a->used] = i;

 a->used++;
}

void array_delete(array* a) {
 free(a->data);
}

void array_delete_all(array* a) {
 int i;

 for(i = 0; i < a->used; i++)
  free((void*)a->data[i]);

 array_delete(a);
}

void array_swap(array* a, int x, int y) {
 int temp = a->data[x];

 a->data[x] = a->data[y];
 a->data[y] = temp;
}

int array_partition(array* a, int s, int e, int (*fp_less)(int, int)) {
 int i = s - 1, j, center = (s + e) / 2;
 int temp;

 if(fp_less(a->data[center], a->data[s]))
  array_swap(a, center, s);
 
 if(fp_less(a->data[e], a->data[s]))
  array_swap(a, e, s);
 
 if(fp_less(a->data[e], a->data[center]))
  array_swap(a, e, center);

 temp = a->data[e];

 for(j = s; j <= e - 1; j++) {
  if(fp_less(a->data[j], temp)) {
   i++;

   array_swap(a, i, j);
  }
 }

 array_swap(a, i + 1, e);

 return i + 1;
}

int array_min(array* a, int s, int e, int (*fp_less)(int, int)) {
 int index = s, i;

 for(i = s + 1; i <= e; i++) {
  if(fp_less(a->data[i], a->data[index]))
   index = i;
 }

 return index;
}

void array_insertionsort(array* a, int s, int e, int (*fp_less)(int, int)) {
 int i, u;

 array_swap(a, array_min(a, s, e, fp_less), s);
 
 for(i = s + 2; i <= e; i++) {
  u = i;

  while(a->data[u] < a->data[u - 1]) {
   array_swap(a, u, u - 1);

   u--;
  }
 }
}

void array_quicksort(array* a, int s, int e, int (*fp_less)(int, int)) {
 if(e > s + 8) {
  int c = array_partition(a, s, e, fp_less);

  array_quicksort(a, s, c - 1, fp_less);
  array_quicksort(a, c + 1, e, fp_less);
 } else 
  array_insertionsort(a, s, e, fp_less);
}

void array_sort(array* a, int (*fp_less)(int, int)) {
 if(a->used)
  array_quicksort(a, 0, a->used - 1, fp_less); 
}

inline int array_binary_search_within(array* a, int el, int start, int end) {
 int s = start, e = end, center;

 while(s <= e) {
  center = (s + e) / 2;

  if(el < a->data[center])
   e = center -1;
  else if(el > a->data[center])
   s = center + 1;
  else
   return center;
 }

 return -1;
}

inline int array_binary_search(array* a, int e) {
 return array_binary_search_within(a, e, 0, a->used - 1);
}

void array_finalize(array* a) { /* set real size = used size */
 if(a->used) {
  a->data = (int*)realloc(a->data, a->used * sizeof(int));
 
  a->size = a->used;
 }
}

