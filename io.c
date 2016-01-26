#include <stdio.h>
#include <stdlib.h>
#define LCP_EOF '\t'

// linux vs. windows PROBLEM!!!
void io_str_input(char* filename, char** dst, int* len) {
  FILE* file = fopen(filename, "r");
  fseek(file, 0, SEEK_END);
  *len = ftell(file); // in linux " - 1" should be removed because windows makes new line in file with 2 character: \r\n 
  printf("%d\n",*len);
  fseek(file, 0, SEEK_SET);
  *dst = (char*)malloc((*len + 1) * sizeof(char));
  fscanf(file, "%s", *dst);
  (*dst)[*len - 1] = LCP_EOF;
  (*dst)[*len] = 0;
  fclose(file);
}

void io_int_output(char* filename, int* data, int len) {
  FILE* file = fopen(filename, "w");
  int i = 0;
  for (i = 1; i <= len + 1; i++) {
    fprintf(file, "%d\n", data[i]);
  }
  fclose(file);
}

void io_str_output(char* filename, char* data, int len) {
  FILE* file = fopen(filename, "w");
  fprintf(file, "%s\n", data);
  fclose(file);
}
