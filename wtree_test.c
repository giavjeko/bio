#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "wtree.c"

void test_wtree_compare() {
}

void test_wtree_construct() {
  char *alphabet = "abcde";
  Atom* wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(! strcmp(wtree->abc, "abcde"));
  assert(! strcmp(wtree->left->abc, "abc"));
  assert(! strcmp(wtree->left->left->abc, "ab"));
  assert(! strcmp(wtree->left->left->left->abc, "a"));
  assert(! strcmp(wtree->left->left->right->abc, "b"));
  assert(! strcmp(wtree->left->right->abc, "c"));
  assert(! strcmp(wtree->right->abc, "de"));
  assert(! strcmp(wtree->right->left->abc, "d"));
  assert(! strcmp(wtree->right->right->abc, "e"));
  assert(wtree_is_leaf(wtree->left->left->left));
  assert(wtree_is_leaf(wtree->left->left->right));
  assert(wtree_is_leaf(wtree->right->left));
  assert(wtree_is_leaf(wtree->right->right));
  printf("Wtree construct OK\n");
}

void test_wtree_tostring() {
}

void test_wtree_push() {
}

int main(void) {
  printf("Wtree module running tests\n");
  test_wtree_compare();
  test_wtree_construct();
  test_wtree_tostring();
  test_wtree_push();
  printf("Wtree module all tests passed\n");
  return 0;
}
