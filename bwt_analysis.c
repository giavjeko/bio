#include <stdio.h>
#include <string.h>
#include "io.c"
#include "sais.c"

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s input_file_path\n", *argv);
    exit(1);
  }
  char* input_path = *(argv + 1);
  int len;
  char* string;

  io_str_input(input_path, &string, &len);
  char* bwt = (char*)malloc((len + 1) * sizeof(char));
  int* A = (int*)malloc(len * sizeof(int));
  sais_bwt(string, bwt, A, len);

  return 0;
}
