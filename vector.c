#include <stdlib.h>
#include <string.h>

typedef struct Vector Vector;
struct Vector {
  int len;
  int full;
  char* data;
};

Vector* vector_construct(){
  Vector* vector = (Vector*)malloc(sizeof(Vector));
  vector->len = 1;
  vector->full = 0;
  vector->data = (char*)malloc(2 * sizeof(char));
  vector->data[0] = 0;
  return vector;
}

int vector_is_full(Vector *vector) {
  return vector->len == vector->full;
}

void vector_extend(Vector *vector) {
  vector->data = (char*)realloc(vector->data, (vector->len * 2 + 1) * sizeof(char));
  vector->len *= 2;
}

void vector_push(Vector *vector, char ch) {
  vector->data[vector->full++] = ch;
  vector->data[vector->full] = 0;
  if (vector_is_full(vector)) {
    vector_extend(vector);
  }
}

int vector_contains(Vector *vector, char ch) {
  return strchr(vector->data, ch) != NULL;
}
