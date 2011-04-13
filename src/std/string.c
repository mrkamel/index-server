
#include "string.h"

#include <stdlib.h>

#define STRING_GROW 20

uchar pearson[256] = {
 251, 175, 119, 215, 81, 14, 79, 191, 103, 49, 181, 143, 186, 157,  0,
 232, 31, 32, 55, 60, 152, 58, 17, 237, 174, 70, 160, 144, 220, 90, 57,
 223, 59,  3, 18, 140, 111, 166, 203, 196, 134, 243, 124, 95, 222, 179,
 197, 65, 180, 48, 36, 15, 107, 46, 233, 130, 165, 30, 123, 161, 209, 23,
 97, 16, 40, 91, 219, 61, 100, 10, 210, 109, 250, 127, 22, 138, 29, 108,
 244, 67, 207,  9, 178, 204, 74, 98, 126, 249, 167, 116, 34, 77, 193,
 200, 121,  5, 20, 113, 71, 35, 128, 13, 182, 94, 25, 226, 227, 199, 75,
 27, 41, 245, 230, 224, 43, 225, 177, 26, 155, 150, 212, 142, 218, 115,
 241, 73, 88, 105, 39, 114, 62, 255, 192, 201, 145, 214, 168, 158, 221,
 148, 154, 122, 12, 84, 82, 163, 44, 139, 228, 236, 205, 242, 217, 11,
 187, 146, 159, 64, 86, 239, 195, 42, 106, 198, 118, 112, 184, 172, 87,
 2, 173, 117, 176, 229, 247, 253, 137, 185, 99, 164, 102, 147, 45, 66,
 231, 52, 141, 211, 194, 206, 246, 238, 56, 110, 78, 248, 63, 240, 189,
 93, 92, 51, 53, 183, 19, 171, 72, 50, 33, 104, 101, 69, 8, 252, 83, 120,
 76, 135, 85, 54, 202, 125, 188, 213, 96, 235, 136, 208, 162, 129, 190,
 132, 156, 38, 47, 1, 7, 254, 24, 4, 216, 131, 89, 21, 28, 133, 37, 153,
 149, 80, 170, 68, 6, 169, 234, 151
};

void string_grow(string* s) {
 if(s->used >= s->size) {
  s->data = (char*)realloc(s->data, (s->size + STRING_GROW + 1) * sizeof(char));

  s->size += STRING_GROW;
 }
}

void string_init(string* s) {
 s->data = 0;
 s->used = 0;
 s->size = 0;
}

void string_concat(string* s, char c) {
 string_grow(s);

 s->data[s->used] = c;
 s->data[s->used + 1] = 0;

 s->used++;
}

void string_concat_string(string* s, char* chars) {
 while(*chars) {
  string_concat(s, *chars);

  chars++;
 }
}

void string_split(string* s, array* a, char c) {
 string *current;
 int i;

 current = (string*)malloc(sizeof(string));

 string_init(current);

 for(i = 0; i < s->used; i++) {
  if(s->data[i] != c)
   string_concat(current, s->data[i]);
  else if(current->used) {
   array_push(a, (int)current);

   current = (string*)malloc(sizeof(string));

   string_init(current);
  }
 }

 if(current->used)
  array_push(a, (int)current);
 else
  free(current);
}

void string_delete(string* s) {
 free(s->data);

 string_init(s);
}

uint string_hash(string* s) {
 uchar hash[4] = { s->used };
 int i, u;

 for(i = 0; i < 4; i++)
  hash[i] = s->data[i % s->used];

 for(i = 0; i < s->used; i++) {
  for(u = 0; u < 4; u++)
   hash[u] = pearson[hash[u] ^ (uchar)s->data[i]];
 }

 return *(uint*)hash;
}

void string_array_delete(array* arr) {
 int i;

 for(i = 0; i < arr->used; i++)
  string_delete((string*)arr->data[i]);

 array_delete_all(arr);
}

void string_empty(string* str) {
 if(str->used)
  str->data[0] = 0;

 str->used = 0;
}

