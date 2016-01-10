#include <stdio.h>
#include <string.h>
#include "bwt.c"
#include "wtree.c"
#include "set.c"

char* generate_alphabet(char* string, int len) {
  Set* set = set_construct();
  int i;
  for (i = 0; i < len; i++) {
    set_push(set, string[i]);
  }
  return set_tostring(set);
}

Wtree* generate_wtree(char* string, int string_len, char* alphabet, int alphabet_len) {
  Wtree* wtree = wtree_construct(alphabet, alphabet_len);
  int i;
  for (i = 0; i < string_len; i++) {
    wtree_push(wtree, string[i]);
  }
  return wtree;
}

int main () {
  char* input = "el_anele_lepanelen$";
  char* alphabet = generate_alphabet(input, strlen(input));
  char* bwt = (char*)malloc((strlen(input) + 1) * sizeof(char));
  bwt_transform(input, bwt, strlen(input));
  Wtree* wtree = generate_wtree(input, strlen(input), alphabet, strlen(alphabet));

  printf("%s\n%s\n%s\n\n%s\n", input, alphabet, bwt, wtree_tostring(wtree));
  return 0;
}
