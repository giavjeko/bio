#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bitvector.c"

int main() {

  // Word length
  int word_length = bitvector_get_word_length();
  assert(word_length == 64);
  printf("Word length OK\n");

  // Word to string
  Word word = (Word)12345678908772728371u;
  char* string = "1010101101010100101010011000111010101100011011100011111000110011";
  char* result = bitvector_word_tostring(&word, strlen(string));
  assert(! strcmp(result, string));
  printf("Word to string OK\n");

  // Construct
  Bitvector* bitvector = bitvector_construct(100);
  assert(bitvector->length == 0);
  printf("Bitvector construct OK\n");

  // Push
  int i;
  char* expected = "10101011010101001010100110001110101011000110111000111110001100110000011111";
  for (i = 0; i < strlen(expected); i++) {
    bitvector_push(bitvector, expected[i] == '1');
  }
  assert(bitvector->length == strlen(expected));
  printf("Bitvector push OK\n");

  // Bitvector to string
  char* vector = bitvector_tostring(bitvector);
  assert(! strcmp(vector, expected));
  printf("Bitvector to string OK\n");

  return 0;
}
