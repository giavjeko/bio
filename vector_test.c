#include <stdio.h>
#include <assert.h>
#include "vector.c"

void test_vector_construct() {
  Vector* vector = vector_construct();
  assert(vector->len == 1);
  assert(vector->full == 0);
  assert(! strcmp(vector->data, ""));
  printf("Vector construct OK\n");
}

void test_vector_is_full() {
  Vector* vector = vector_construct();
  assert(! vector_is_full(vector));
  vector_push(vector, 'a');
  assert(! vector_is_full(vector));
  printf("Vector is full OK\n");
}

void test_vector_extend() {
  Vector* vector = vector_construct();
  int len = vector->len;
  vector_extend(vector);
  assert(vector->len = 2 * len);
  printf("Vector extend OK\n");
}

void test_vector_push() {
  Vector* vector = vector_construct();
  vector_push(vector, 'a');
  vector_push(vector, 'b');
  assert(vector->full == 2);
  assert(! strcmp(vector->data, "ab"));
  printf("Vector push OK\n");
}

void test_vector_contains() {
  Vector *vector = vector_construct();
  vector_push(vector, 'a');
  vector_push(vector, 'b');
  assert(vector_contains(vector, 'a'));
  assert(! vector_contains(vector, 'c'));
  printf("Vector contains OK\n");
}

int main () {
  printf("Vector module running tests\n");
  test_vector_construct();
  test_vector_is_full();
  test_vector_extend();
  test_vector_push();
  printf("Vector module all tests pass\n");
  return 0;
}
