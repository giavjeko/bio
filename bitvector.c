#include <string.h>
#include <stdlib.h>

typedef char Bit;
typedef unsigned long long Word;
typedef struct Bitvector Bitvector;
struct Bitvector {
  Word* data;
  int length, capacity;
};

int bitvector_get_word_length() {
  return sizeof(Word) * 8;
}

Bitvector* bitvector_construct() {
  int word_length = bitvector_get_word_length();
  Bitvector* bitvector = (Bitvector*)malloc(sizeof(Bitvector));
  bitvector->length = 0;
  bitvector->capacity = word_length;
  bitvector->data = (Word*)malloc(sizeof(Word));
  return bitvector;
}

int bitvector_is_full(Bitvector* bitvector) {
  return bitvector->length == bitvector->capacity;
}

void bitvector_expand(Bitvector* bitvector) {
  int word_length = bitvector_get_word_length();
  bitvector->capacity *= 2;
  int word_count = bitvector->capacity / word_length;
  bitvector->data = (Word*)realloc(bitvector->data, word_count * sizeof(Word));
}

void bitvector_push(Bitvector* bitvector, Bit bit) {
  int word_length = bitvector_get_word_length();
  int current_word_index = bitvector->length / word_length;
  bitvector->data[current_word_index] <<= 1;
  bitvector->data[current_word_index] |= (Word)(bit ? 1 : 0);
  bitvector->length++;
  if (bitvector_is_full(bitvector)) {
    bitvector_expand(bitvector);
  }
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
