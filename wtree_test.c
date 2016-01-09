#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "wtree.c"

void test_wtree_compare() {
}

void test_wtree_generate() {
}

void test_wtree_tostring() {
}

void test_wtree_push() {
}

int main(void) {
  printf("Wtree module running tests\n");
  test_wtree_compare();
  test_wtree_generate();
  test_wtree_tostring();
  test_wtree_push();
  printf("Wtree module all tests passed\n");
  return 0;
}
