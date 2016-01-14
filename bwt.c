#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Implements Burrows–Wheeler transform algorithm

// Rotate given src string and store result into given dst string
void bwt_rotate_left(const char* src, char* dst, int len) {
  int i;
  for (i = 1; i < len; i++) {
    dst[i - 1] = src[i];
  }
  dst[len - 1] = src[0];
  dst[len] = 0;
}

// Generate all rotations of src string and store them into dst matrix
void bwt_generate_rotations(const char* src, char** dst, int len) {
  int i;
  strncpy(dst[0], src, len);
  for (i = 1; i < len; i++) {
    bwt_rotate_left(dst[i - 1], dst[i], len);
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
  int i;
  // Allocate memory
  char** rotations = (char**)malloc(len * sizeof(char*));
  for (i = 0; i < len; i++) {
    rotations[i] = (char*)malloc((len + 1) * sizeof(char*));
  }

  bwt_generate_rotations(src, rotations, len);
  bwt_sort_strings(rotations, len);
  bwt_get_last_column(rotations, dst, len);

  // Free memory
  for (i = 0; i < len; i++) {
    free(rotations[i]);
  }
  free(rotations);
}
