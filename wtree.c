#include <string.h>
#include <stdlib.h>
#include "vector.c"
#include "bitvector.c"

typedef struct at Atom;
struct at {
  char* abc;
  Bitvector* bitvector;
  Atom* left;
  Atom* right;
};

int wtree_compare(const void *a, const void *b) {
  return ( *(char*)a - *(char*)b );
}

int wtree_is_leaf(Atom* atom) {
  return atom->abc[1] == 0;
}

Atom* wtree_construct(char* alphabet, int len) {
  Atom* node = (Atom*)malloc(sizeof(Atom));
  node->abc = (char*)malloc((len + 1) * sizeof(char));
  strcpy(node->abc, alphabet);
  int left_len = len - len / 2;
  int right_len = len / 2;

  if (len > 1) {
    node->bitvector = bitvector_construct();
    char* left_alphabet = (char*)malloc((left_len + 1) * sizeof(char));
    char* right_alphabet = (char*)malloc((right_len + 1) * sizeof(char));

    strncpy(left_alphabet, alphabet, left_len);
    left_alphabet[left_len] = '\0';

    strncpy(right_alphabet, alphabet + left_len, right_len);
    right_alphabet[right_len] = '\0';

    node->left = wtree_construct(left_alphabet, left_len);
    node->right = wtree_construct(right_alphabet, right_len);
  } else {
    node->left = NULL;
    node->right = NULL;
  }

  return node;
}

void wtree_tostring(Atom *wtree, int depth, char **out){
  int i = 0;

  if (depth == 0) *out = (char *) malloc( (strlen(wtree->abc)+2) * sizeof(char));
  else *out = (char *) realloc(*out, (strlen(*out) + strlen(wtree->abc)+2+depth) * sizeof(char));

  if (!wtree_is_leaf(wtree)) {
    for (i = 0; i < depth; i++) strcat(*out,"-");
    if (depth == 0) strcpy(*out,wtree->abc);
    else strcat(*out,wtree->abc);
    strcat(*out,"\n");
    wtree_tostring(wtree->left,depth+1,out);
    wtree_tostring(wtree->right,depth+1,out);
  }
  else {
    *out = (char *) realloc(*out, (strlen(*out) + strlen(wtree->abc)+2+depth) * sizeof(char));
    for (i = 0; i < depth; i++) strcat(*out,"-");
    if (depth == 0) strcpy(*out,wtree->abc);
    else strcat(*out,wtree->abc);
    strcat(*out,"\n");
  }
}

void wtree_push(Atom *wtree, char ch){
  while (! wtree_is_leaf(wtree)) {
    if (strchr(wtree->left->abc, ch) != NULL) {
      bitvector_push(wtree->bitvector, (Bit)0);
      wtree = wtree->left;
    } else {
      bitvector_push(wtree->bitvector, (Bit)1);
      wtree = wtree->right;
    }
  }
}

