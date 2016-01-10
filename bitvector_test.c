#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bitvector.c"

char* data = "10101011010101001010100110001110101011000110111000111110001100110000011111";
int rank = 39;
int word1rank = 34;

void populate_bitvector(Bitvector* bitvector) {
  int i;
  for (i = 0; i < strlen(data); i++) {
    bitvector_push(bitvector, data[i] == '1');
  }
}

void test_bitvector_get_word_length() {
  int word_length = bitvector_get_word_length();
  assert(word_length == 64);
  printf("Word length OK\n");
}

void test_bitvector_construct() {
  Bitvector* bitvector = bitvector_construct();
  int word_length = bitvector_get_word_length();
  assert(bitvector->length == 0);
  assert(bitvector->capacity == word_length);
  printf("Bitvector construct OK\n");
}

void test_bitvector_is_full() {
  int word_length = bitvector_get_word_length();
  Bitvector* bitvector = bitvector_construct();
  assert(! bitvector_is_full(bitvector));
  populate_bitvector(bitvector);
  assert(! bitvector_is_full(bitvector));
  assert(bitvector->capacity == 2 * word_length);
  bitvector_push(bitvector, (Bit)1);
  assert(! bitvector_is_full(bitvector));
  printf("Bitvector is full OK\n");
}

void test_bitvector_expand() {
  Bitvector* bitvector = bitvector_construct();
  int word_length = bitvector_get_word_length();
  assert(bitvector->capacity == word_length);
  bitvector_expand(bitvector);
  assert(bitvector->capacity == word_length * 2);
  printf("Bitvector expand OK\n");
}

void test_bitvector_push() {
  Bitvector* bitvector = bitvector_construct();
  populate_bitvector(bitvector);
  char* string = bitvector_tostring(bitvector);
  assert(bitvector->length == strlen(data));
  assert(! strcmp(string, data));
  assert(bitvector->rank[0] == word1rank);
  assert(bitvector->rank[1] == rank - word1rank);
  printf("Bitvector push OK\n");
}

void test_bitvector_rank() {
  Bitvector* bitvector = bitvector_construct();
  populate_bitvector(bitvector);
  assert(bitvector_rank(bitvector, 0) == 0);
  assert(bitvector_rank(bitvector, 8) == 5);
  assert(bitvector_rank(bitvector, 64) == word1rank);
  assert(bitvector_rank(bitvector, 70) == 35);
  printf("Bitvector rank OK\n");
}

void test_bitvector_word_tostring() {
  Word word = (Word)12345678908772728371u;
  char* string = "1010101101010100101010011000111010101100011011100011111000110011";
  char* result = bitvector_word_tostring(&word, strlen(string));
  assert(! strcmp(result, string));
  printf("Word to string OK\n");
}

void test_bitvector_tostring() {
  Bitvector* bitvector = bitvector_construct();
  populate_bitvector(bitvector);
  char* string = bitvector_tostring(bitvector);
  assert(! strcmp(string, data));

  bitvector = bitvector_construct();
  string = bitvector_tostring(bitvector);
  assert(! strcmp(string, ""));

  printf("Bitvector to string OK\n");
}

int main(void) {
  printf("Bitvector module running tests\n");
  test_bitvector_get_word_length();
  test_bitvector_construct();
  test_bitvector_is_full();
  test_bitvector_expand();
  test_bitvector_push();
  test_bitvector_rank();
  test_bitvector_word_tostring();
  test_bitvector_tostring();
  printf("Bitvector module all tests passed\n");
  return 0;
}
