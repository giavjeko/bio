#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Implements Burrows–Wheeler transform algorithm

// Generate all rotations of src string and store them into dst matrix
void bwt_generate_rotations(char* src, char** dst, int len) {
  int i = 0;
  for (i = 0; i < len; i++) {
    dst[i] = src + i;
  }
}

// Helper funcion for string sort
int bwt_compare(const void *a, const void *b) {
  char* str_a = *(char**)a;
  char* str_b = *(char**)b;
  return strcmp(str_a, str_b);
}

// Sort given array of strings
void bwt_sort_strings(char** strings, int len) {
  qsort(strings, len, sizeof(char*), bwt_compare);
}

// Get last column of all BWT rotations matrix
void bwt_get_last_column(char** src, char* dst, int len) {
  int i;
  for (i = 0; i < len; i++) {
    dst[i] = src[i][len - 1];
  }
  dst[len] = 0;
}

// Perform BWT transform on src, store result into dst
void bwt_transform(const char* src, char* dst, int len) {
  // Allocate memory
  char* rotations_storage = (char*)malloc((2 * len + 1) * sizeof(char));
  char** rotations = (char**)malloc(len * sizeof(char*));
  strcpy(rotations_storage, src);
  strcat(rotations_storage, src);

  bwt_generate_rotations(rotations_storage, rotations, len);
  bwt_sort_strings(rotations, len);
  bwt_get_last_column(rotations, dst, len);

  // Free memory
  free(rotations);
  free(rotations_storage);
}
