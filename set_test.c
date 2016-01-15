#include <stdio.h>
#include <assert.h>
#include "set.c"

void test_set_construct() {
  Set* set = set_construct();
  assert(set->capacity == 1);
  assert(set->size == 0);
  assert(! strcmp(set->data, ""));
  printf("\tSet construct test passed\n");
}

void test_set_is_full() {
  Set* set = set_construct();
  assert(! set_is_full(set));
  set_push(set, 'a');
  assert(! set_is_full(set));
  printf("\tSet is full test passed\n");
}

void test_set_extend() {
  Set* set = set_construct();
  int capacity = set->capacity;
  set_extend(set);
  assert(set->capacity = 2 * capacity);
  printf("\tSet extend test passed\n");
}

void test_set_push() {
  Set* set = set_construct();
  int return_value;
  return_value = set_push(set, 'a');
  assert(return_value == 1);
  return_value = set_push(set, 'b');
  assert(return_value == 1);
  assert(set->size == 2);
  return_value = set_push(set, 'b');
  assert(return_value == 0);
  assert(set->size == 2);
  assert(! strcmp(set->data, "ab"));
  printf("\tSet push test passed\n");
}

void test_set_contains() {
  Set *set = set_construct();
  set_push(set, 'a');
  set_push(set, 'b');
  assert(set_contains(set, 'a'));
  assert(! set_contains(set, 'c'));
  printf("\tSet contains test passed\n");
}

int main () {
  printf("Set module running tests\n");
  test_set_construct();
  test_set_is_full();
  test_set_extend();
  test_set_push();
  printf("Set module all tests pass\n");
  return 0;
}
