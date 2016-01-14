#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%^&*()_+[]{}\\'\"<>?:;";

void get_sample(char* src, int src_len, char* dst, int dst_len) {
  assert(dst_len <= src_len);
  int segment_len = src_len / dst_len;
  int dst_index = 0;
  for (int i = 0; i <= src_len; i+= segment_len) {
    int offset = rand() % segment_len;
    dst[dst_index++] = src[i + offset];
  }
}

int main(int argc, char** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s alphabet_length string_lengh output_file_path\n", *argv);
    exit(1);
  }

  int sample_len = atoi(*(argv + 1));
  int total_len = atoi(*(argv + 2));
  char* output = *(argv + 3);

  int alphabet_len = strlen(alphabet);
  char sample[100];
  get_sample(alphabet, alphabet_len, sample, sample_len);

  FILE* file = fopen(output, "w");
  srand(time(0));
  for (int i = 0; i < total_len; i++) {
    int index = rand() % sample_len;
    char ch = sample[index];
    fputc(ch, file);
  }
  fputc('\n', file);
  fclose(file);

  return 0;
}
