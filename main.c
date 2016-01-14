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

  dst[0] = -1;
  dst[len - 1] = -1;
  for (i = 1; i < len - 1; i++) {
    dst[i] = -2;
  }

  queue_push(queue, 1, len, 0);
  while(!queue_empty(queue)) {
    queue_pop(queue, &begin, &end, &l);
    list = wtree_get_intervals(wtree, begin, end);
    for (element = list->head; element; element=element->next) {
      if (dst[element->end] == -2) {
        queue_push(queue, element->begin, element->end, l + 1);
        dst[element->end] = l;
      }
    }
  }

}

int main() {
  char* input = "el_anele_lepanelen$";
  int len = strlen(input);
  char* alphabet = generate_alphabet(input, len);
  char* bwt = (char*)malloc((strlen(input) + 1) * sizeof(char));
  bwt_transform(input, bwt, strlen(input));
  Wtree* wtree = generate_wtree(bwt, strlen(input), alphabet, strlen(alphabet));
  printf("%s\n%s\n%s\n\n%s\n", input, alphabet, bwt, wtree_tostring(wtree));

  int* lcp = (int*)malloc(len * sizeof(int));
  compute_lcp(wtree, lcp, len);
  printf("lcp:\n");
  int i;
  for (i = 0; i < len; i++) {
    printf("%d ", lcp[i]);
  }
  printf("\n");
  return 0;
}
