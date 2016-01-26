#include <stdio.h>
#include <string.h>
#include "io.c"
#include "sais.c"
#include "wtree.c"
#include "queue.c"

#define LCP_EOF '\t'

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
    list_destroy(list);
  }
}

void bwt_transform(char* string, char* result, int len) {
  int i;
  int* A = (int*)malloc(len * sizeof(int));
  int eof_pos = sais_bwt(string, result, A, len);
  assert(eof_pos > 0);
  char eof = result[0];
  for (i = 0; i < eof_pos - 1; i++) {
    result[i] = result[i+1];
  }
  result[eof_pos - 1] = eof;
  result[len] = 0;
  free(A);
}

void process(char* string, int* result, int len) {
  char* bwt = (char*)malloc((len + 1) * sizeof(char));
  bwt_transform(string, bwt, len);
  Wtree* wtree = wtree_generate(bwt, len);
  free(bwt);
  compute_lcp(wtree, result, len);
  free(wtree);
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

  io_str_input(input_path, &string, &len);
  int* result = (int*)malloc((len + 2) * sizeof(int));
  process(string, result, len);
  io_int_output(output_path, result, len);
  free(result);

  return 0;
}
