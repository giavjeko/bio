#include <string.h>
#include <stdlib.h>
#include "bitvector.h"

int bitvector_get_word_length() {
  return sizeof(Word) * 8;
}

Bitvector* bitvector_construct(int length) {
  int word_length = bitvector_get_word_length();
  int word_count = length / word_length + (length % word_length) ? 1 : 0;
  Bitvector* bitvector = (Bitvector*)malloc(sizeof(Bitvector));
  bitvector->data = (Word*)malloc(word_count * sizeof(Word));
  bitvector->length = 0;
  return bitvector;
}

void bitvector_push(Bitvector* bitvector, Bit bit) {
  int word_length = bitvector_get_word_length();
  int current_word_index = bitvector->length / word_length;
  bitvector->data[current_word_index] <<= 1;
  bitvector->data[current_word_index] |= (Word)(bit ? 1 : 0);
  bitvector->length++;
}

char* bitvector_word_tostring(Word* word, int length) {
  char* result = (char*)malloc(length * sizeof(char) + 1);
  Word mask = (Word)1;
  int i;
  for (i = 0; i < length; i++) {
    result[length - i - 1] = (*word & mask) ? '1' : '0';
    mask <<= 1;
  }
  return result;
}

char* bitvector_tostring(Bitvector* bitvector) {
  int word_length = bitvector_get_word_length();
  int current_word_index = bitvector->length / word_length;
  char* result = (char*)malloc(bitvector->length * sizeof(char) + 1);
  int i;
  for (i = 0; i <= current_word_index; i++) {
    int word_usage = (i < current_word_index) ? word_length : bitvector->length % word_length;
    char* word = bitvector_word_tostring(&bitvector->data[i], word_usage);
    strcat(result, word);
    free(word);
  }
  return result;
}
