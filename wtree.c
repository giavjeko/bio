// Implements wavelet tree structure

#include <string.h>
#include <stdlib.h>
#include "bitvector.c"
#include "set.c"
#include "list.c"

typedef struct Atom Atom;
struct Atom {
  char* alphabet;
  Bitvector* bitvector;
  Atom* left;
  Atom* right;
};

typedef struct Wtree Wtree;
struct Wtree {
  Atom* root;
  char* alphabet;
  int* char_rank;
  int char_rank_len;
};

// Helper function used to sort string
int wtree_compare(const void *a, const void *b) {
  return ( *(char*)a - *(char*)b );
}

// Returin true telling if given wtree node is leaf
int wtree_node_isleaf(Atom* atom) {
  return atom->alphabet[1] == 0;
}

// Allocate memory and initialize empty wavelet tree node
Atom* wtree_node_construct(char* alphabet, int len) {
  Atom* node = (Atom*)malloc(sizeof(Atom));
  node->alphabet = (char*)malloc((len + 1) * sizeof(char));
  strcpy(node->alphabet, alphabet);
  int left_len = len - len / 2;
  int right_len = len / 2;

  node->bitvector = bitvector_construct();

  if (len > 1) {
    char* left_alphabet = (char*)malloc((left_len + 1) * sizeof(char));
    char* right_alphabet = (char*)malloc((right_len + 1) * sizeof(char));

    strncpy(left_alphabet, alphabet, left_len);
    left_alphabet[left_len] = '\0';

    strncpy(right_alphabet, alphabet + left_len, right_len);
    right_alphabet[right_len] = '\0';

    node->left = wtree_node_construct(left_alphabet, left_len);
    node->right = wtree_node_construct(right_alphabet, right_len);
  } else {
    node->left = NULL;
    node->right = NULL;
  }

  return node;
}

// Allocate memory and initialize empty wavelet tree
Wtree* wtree_construct(char* alphabet, int len) {
  int i;
  Wtree* wtree = (Wtree*)malloc(sizeof(Wtree));
  wtree->root = wtree_node_construct(alphabet, len);
  wtree->alphabet = wtree->root->alphabet;
  wtree->char_rank_len = len;
  wtree->char_rank = (int*)malloc(len * sizeof(int));
  for (i = 0; i < len; i++) {
    wtree->char_rank[i] = 0;
  }
  return wtree;
}

// Generate string representation of given wavelet tree node
char *wtree_node_tostring(Atom *node) {
  char *out;
  char *bvstr;

  if (! wtree_node_isleaf(node)) {
    bvstr = bitvector_tostring(node->bitvector);
    out = (char *) malloc( (strlen(node->alphabet) + strlen(bvstr) + 2) * sizeof(char));
    strcpy(out, node->alphabet);
    strcat(out,"_");
    strcat(out, bvstr);
  } else {
    out = (char *) malloc( 2 * sizeof(char));
    strcpy(out, node->alphabet);
  }

  return out;
}

// Recursively generate string representation of given wavelet tree
void wtree_tostring_recursion(Atom *node, int depth, char **out) {
  int i = 0;
  char *tmp;

  tmp = wtree_node_tostring(node);
  *out = (char *) realloc(*out, (strlen(*out) + strlen(tmp)+2 + depth) * sizeof(char));

  for (i = 0; i < depth; i++) strcat(*out,"-");
  strcat(*out, tmp);
  strcat(*out,"\n");
  if (!wtree_node_isleaf(node)) {
    wtree_tostring_recursion(node->left, depth + 1, out);
    wtree_tostring_recursion(node->right, depth + 1, out);
  }
}

// Generate string representation of given number
char* wtree_int_tostring(int number) {
  int length, temp = number;
  if (! number) {
    return "0";
  }
  for (length = 0; temp; temp /= 10) {
    length++;
  }
  char* result = (char*)malloc((length + 1) * sizeof(char));
  int i;
  for (i = length; number; number /= 10) {
    result[--i] = (char)('0' + number % 10);
  }
  result[length] = 0;
  return result;
}

// Generate string representation of given wavelet tree
char *wtree_tostring(Wtree *wtree) {
  char *itos = wtree_int_tostring(wtree->char_rank_len);
  int i, len = strlen(itos)+3 + 1;
  char *out = (char *) malloc(len * sizeof(char));
  strcpy(out, itos);
  strcat(out," -");
  for (i = 0; i < wtree->char_rank_len; i++) {
    strcat(out," ");
    itos = wtree_int_tostring(wtree->char_rank[i]);
    len += strlen(itos)+1;
    out = (char *) realloc(out, len * sizeof(char));
    strcat(out, itos);
  }
  strcat(out,"\n");
  wtree_tostring_recursion(wtree->root, 0, &out);
  return out;
}

// Calculate C array with new alphabet characted
void wtree_update_char_rank(Wtree* wtree, char ch) {
  int i = strchr(wtree->alphabet, ch) - wtree->alphabet;
  for (i = i + 1; i < wtree->char_rank_len; i++) {
    wtree->char_rank[i]++;
  }
}

// Push given char into given wtree
void wtree_push(Wtree *wtree, char ch) {
  Atom* node = wtree->root;
  while (! wtree_node_isleaf(node)) {
    if (strchr(node->left->alphabet, ch) != NULL) {
      bitvector_push(node->bitvector, (Bit)0);
      node = node->left;
    } else {
      bitvector_push(node->bitvector, (Bit)1);
      node = node->right;
    }
  }
  wtree_update_char_rank(wtree, ch);
}

Wtree* wtree_generate(char* string, int len) {
  Set* alphabet = set_construct();
  int i = 0;
  for (i = 0; i < len; i++) {
    set_push(alphabet, string[i]);
  }
  char* alphabet_str = set_tostring(alphabet);
  int alphabet_len = strlen(alphabet_str);
  Wtree* wtree = wtree_construct(alphabet_str, alphabet_len);
  for (i = 0; i < len; i++) {
    wtree_push(wtree, string[i]);
  }
  return wtree;
}

// Recursively calculate sub-intervals for given interval and add results to given list
void wtree_get_intervals_recursion(Wtree* wtree, Atom* node, int begin, int end, List** list) {
  int char_index, char_rank, rank_1_before, rank_1_after, rank_0_before, rank_0_after;
  char leaf_character;

  if (end < begin) {
    return;
  }

  if (wtree_node_isleaf(node)) {
    leaf_character = node->alphabet[0];
    char_index = strchr(wtree->alphabet, leaf_character) - wtree->alphabet;
    char_rank = wtree->char_rank[char_index];
    list_push(*list, char_rank + begin, char_rank + end);
  } else {
    rank_1_before = bitvector_rank(node->bitvector, begin - 1);
    rank_1_after = bitvector_rank(node->bitvector, end);
    rank_0_before = begin - 1 - rank_1_before;
    rank_0_after = end - rank_1_after;
    wtree_get_intervals_recursion(wtree, node->left, rank_0_before + 1, rank_0_after, list);
    wtree_get_intervals_recursion(wtree, node->right, rank_1_before + 1, rank_1_after, list);
  }
}

// Calculate sub-intervals for given interval in given wavelet tree
List* wtree_get_intervals(Wtree* wtree, int begin, int end) {
  List* list = list_construct();
  wtree_get_intervals_recursion(wtree, wtree->root, begin, end, &list);
  return list;
}
