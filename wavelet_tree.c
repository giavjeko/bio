#include <string.h>
#include "bitvector.c"
#include "wavelet_tree.h"

wavelet_node_construct(char* string, char* left, char* right) {
  Node* node = (Node*)malloc(sizeof Node);
  node->bitvector = bitvector_construct(strlen(string));
  char* symbol;
  for (symbol = string; symbol; symbol++) {
    Bit bit = strchr(right, symbol) ? 1 : 0;
    bitvector_push(bitvector, bit);
  }
}
