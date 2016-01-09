#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "bwt.c"

void test_bwt_rotate_left() {
  char* original = "test";
  char* expected = "estt";
  char result[6];
  bwt_rotate_left(original, result, strlen(original));
  assert(! strcmp(result, expected));
  printf("Rotate left OK\n");
}

void test_bwt_generate_rotations() {
  char* original = "test";
  char** result = (char**)malloc(4 * sizeof(char*));
  int i;
  for (i = 0; i < 4; i++) result[i] = (char*)malloc(5 * sizeof(char));
  bwt_generate_rotations(original, result, strlen(original));
  assert(! strcmp(result[0], "test"));
  assert(! strcmp(result[1], "estt"));
  assert(! strcmp(result[2], "stte"));
  assert(! strcmp(result[3], "ttes"));
  printf("Generate rotations OK\n");
  for (i = 0; i < 4; i++) free(result[i]);
  free(result);
}

void test_bwt_compare() {
  char* a = "abc";
  char* b = "def";
  assert(bwt_compare(&a, &a) == 0);
  assert(bwt_compare(&b, &a) > 0);
  assert(bwt_compare(&a, &b) < 0);
  printf("Compare OK\n");
}

void test_bwt_sort_strings() {
  char* strings[4] = { "1234", "abcd", "0123", "aaaa" };
  bwt_sort_strings(strings, 4);
  assert(! strcmp(strings[0], "0123"));
  assert(! strcmp(strings[1], "1234"));
  assert(! strcmp(strings[2], "aaaa"));
  assert(! strcmp(strings[3], "abcd"));
  printf("Sort strings OK\n");
}

void test_bwt_get_last_column() {
  char* strings[4] = { "abcl", "bsja", "dahs", "jsit" };
  char last_column[5];
  bwt_get_last_column(strings, last_column, 4);
  assert(! strcmp(last_column, "last"));
  printf("Last column OK\n");
}

void test_bwt_transform() {
  char* string = "el_anele_lepanelen$";
  char* expected = "nle_pl$nnlleee_eaae";
  char result[20];
  bwt_transform(string, result, strlen(string));
  assert(! strcmp(result, expected));
  printf("BWT transform OK\n");
}

int main(void) {
  printf("Bwt module running tests\n");
  test_bwt_rotate_left();
  test_bwt_generate_rotations();
  test_bwt_compare();
  test_bwt_sort_strings();
  test_bwt_get_last_column();
  test_bwt_transform();
  printf("Bwt module all tests passed\n");
  return 0;
}
