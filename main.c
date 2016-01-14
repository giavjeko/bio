#include <stdio.h>
#include <string.h>
#include "bwt.c"
#include "wtree.c"
#include "set.c"
#include "queue.c"

// Return alphabet for given string
char* generate_alphabet(char* string, int len) {
  int i;
  Set* set = set_construct();
  for (i = 0; i < len; i++) {
    set_push(set, string[i]);
  }
  return set_tostring(set);
}

// Return Wavelet tree for given string and alphabet
Wtree* generate_wtree(char* string, int string_len, char* alphabet, int alphabet_len) {
  int i;
  Wtree* wtree = wtree_construct(alphabet, alphabet_len);
  for (i = 0; i < string_len; i++) {
    wtree_push(wtree, string[i]);
  }
  return wtree;
}

// Compute lcp for given Wavelet tree with data
void compute_lcp(Wtree* wtree, int* dst, int len) {
  int i, begin, end, l;
  Queue* queue = queue_construct();
  List* list = list_construct();
  Element* element;

  dst[1] = -1;
  dst[len + 1] = -1;
  for (i = 2; i <= len; i++) {
    dst[i] = -2;
  }

  queue_push(queue, 1, len, 0);
  while(!queue_empty(queue)) {
    queue_pop(queue, &begin, &end, &l);
    list = wtree_get_intervals(wtree, begin, end);
    for (element = list->head; element; element=element->next) {
      if (dst[element->end + 1] == -2) {
        queue_push(queue, element->begin, element->end, l + 1);
        dst[element->end + 1] = l;
      }
    }
  }
}

void process(char* string, int* result, int len) {
  char* bwt = (char*)malloc((len + 1) * sizeof(char));
  char* alphabet = generate_alphabet(string, len);
  bwt_transform(string, bwt, len);
  Wtree* wtree = generate_wtree(bwt, len, alphabet, strlen(alphabet));
  compute_lcp(wtree, result, len);
  free(bwt);
  free(alphabet);
  free(wtree);
}

void input(char* filename, char** dst, int* len) {
  FILE* file = fopen(filename, "r");
  fseek(file, 0, SEEK_END);
  *len = ftell(file) - 1;
  fseek(file, 0, SEEK_SET);
  *dst = (char*)malloc((*len + 1) * sizeof(dst));
  fscanf(file, "%s", *dst);
  fclose(file);
}

void output(char* filename, int* data, int len) {
  FILE* file = fopen(filename, "w");
  for (int i = 1; i <= len + 1; i++) {
    fprintf(file, "%d\n", data[i]);
  }
  fclose(file);
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s input_file_path output_file_path\n", *argv);
    exit(1);
  }
  char* input_path = *(argv + 1);
  char* output_path = *(argv + 2);
  int len;
  char* string;

  input(input_path, &string, &len);
  int* result = (int*)malloc((len + 2) * sizeof(int));
  process(string, result, len);
  output(output_path, result, len);
  free(result);

  return 0;
}
