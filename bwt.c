#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bwt_rotate_left(const char* src, char* dst, int len) {
  int i;
  for (i = 1; i < len; i++) {
    dst[i - 1] = src[i];
  }
  dst[len - 1] = src[0];
}

void bwt_generate_rotations(const char* src, char** dst, int len) {
  int i;
  strncpy(dst[0], src, len);
  for (i = 1; i < len; i++) {
    bwt_rotate_left(dst[i - 1], dst[i], len);
  }
}

int bwt_compare(const void *a, const void *b) {
  char* str_a = *(char**)a;
  char* str_b = *(char**)b;
  return strcmp(str_a, str_b);
}

void bwt_sort_strings(char** strings, int len) {
  qsort(strings, len, sizeof(char*), bwt_compare);
}

void bwt_get_last_column(char** src, char* dst, int len) {
  int i;
  for (i = 0; i < len; i++) {
    dst[i] = src[i][len - 1];
  }
  dst[len] = 0;
}

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
