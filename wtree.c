#include <string.h>
#include <stdlib.h>
#include "bitvector.c"
#include "list.c"

typedef struct at Atom;
struct at {
  char* abc;
  Bitvector* bitvector;
  Atom* left;
  Atom* right;
};

typedef struct Wtree Wtree;
struct Wtree {
  Atom* root;
  int* C;
  int Clen;
};

int wtree_compare(const void *a, const void *b) {
  return ( *(char*)a - *(char*)b );
}

int wtree_node_isleaf(Atom* atom) {
  return atom->abc[1] == 0;
}


Atom* wtree_node_construct(char* alphabet, int len) {
  Atom* node = (Atom*)malloc(sizeof(Atom));
  node->abc = (char*)malloc((len + 1) * sizeof(char));
  strcpy(node->abc, alphabet);
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

Wtree* wtree_construct(char* alphabet, int len) {
  int i;
  Wtree* wtree = (Wtree*)malloc(sizeof(Wtree));
  wtree->root = wtree_node_construct(alphabet,len);
  wtree->Clen = len;
  wtree->C = (int*)malloc(len*sizeof(int));
  for (i = 0; i < len; i++) {
    wtree->C[i] = 0;
  }
  return wtree;
}
char *wtree_node_tostring(Atom *node) {
  char *out;
  char *bvstr;
  
  if (! wtree_node_isleaf(node)) {
    bvstr = bitvector_tostring(node->bitvector);
    out = (char *) malloc( (strlen(node->abc) + strlen(bvstr) + 2) * sizeof(char));
    strcpy(out,node->abc);
    strcat(out,"_");
    strcat(out,bvstr);
  }
  else {
    out = (char *) malloc( 2 * sizeof(char));
    strcpy(out,node->abc);
  }
  
  return out;
}

void wtree_tostring_recursion(Atom *node,int depth,char **out) {
  int i = 0;
  char *tmp;
  
  tmp = wtree_node_tostring(node);
  *out = (char *) realloc(*out, (strlen(*out) + strlen(tmp)+2+depth) * sizeof(char));
   
  for (i = 0; i < depth; i++) strcat(*out,"-");
  strcat(*out,tmp);
  strcat(*out,"\n");
  if (!wtree_node_isleaf(node)) {
    wtree_tostring_recursion(node->left,depth+1,out);
    wtree_tostring_recursion(node->right,depth+1,out);
  }                             
}

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

char *wtree_tostring(Wtree *wtree){
  char *itos = wtree_int_tostring(wtree->Clen);
  int i, len = strlen(itos)+3+1;
  char *out = (char *) malloc( len * sizeof(char));
  strcpy(out,itos);
  strcat(out," -");
  for (i = 0; i < wtree->Clen; i++) {
    strcat(out," ");
    itos = wtree_int_tostring(wtree->C[i]);
    len += strlen(itos)+1;
    out = (char *) realloc(out, len * sizeof(char));
    strcat(out,itos);
  }
  strcat(out,"\n");
 
  wtree_tostring_recursion(wtree->root,0,&out);
  
  return out;
}

void wtree_update_C(Wtree* wtree, char ch) {
  int i = strchr(wtree->root->abc, ch) - wtree->root->abc;
  for (i = i+1; i < wtree->Clen; i++) {
    wtree->C[i]++;
  }
}

void wtree_push(Wtree *wtree, char ch){
  Atom* node = wtree->root;
  while (! wtree_node_isleaf(node)) {
    if (strchr(node->left->abc, ch) != NULL) {
      bitvector_push(node->bitvector, (Bit)0);
      node = node->left;
    } else {
      bitvector_push(node->bitvector, (Bit)1);
      node = node->right;
    }
  }
  wtree_update_C(wtree, ch);
}

void wtree_getIntervals_recursion(Wtree* wtree, Atom* node, int i, int j, List** list) {
  int a, b;
  if (wtree_node_isleaf(node)) {
    a = strchr(wtree->root->abc, node->abc[0]) - wtree->root->abc;
    list_push(*list,wtree->C[a]+i,wtree->C[a]+j);
  } else {
    a = i - 1 - bitvector_rank(node->bitvector,i-1);
    b = j - bitvector_rank(node->bitvector,j);
    if (b > a) wtree_getIntervals_recursion(wtree, node->left, a+1, b, list);
    a = i - 1 - a;
    b = j - b;
    if (b > a) wtree_getIntervals_recursion(wtree, node->right, a+1, b, list);
  }
}

List* wtree_getIntervals(Wtree* wtree, int i, int j) {
  List* list = list_construct();
  wtree_getIntervals_recursion(wtree, wtree->root, i, j, &list);
  return list;
}
