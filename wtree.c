#include <string.h>
#include <stdlib.h>
#include "bitvector.c"

/*typedef struct Bitvector Bitvector;
struct Bitvector {
  Word* data;
  int length;
};*/


typedef struct at Atom;
struct at {
  char *abc;
  Bitvector *bitvector;
  Atom *left; 
  Atom *right;
};

typedef struct Vector Vector;
struct Vector {
  int len;
  int full;
  char *data;
  };

Vector *vector_construct(){
  Vector *vector;
  char *new_data;
  if ((vector = (Vector *) malloc(sizeof(Vector))) == NULL) 
    return 0;
  if ((new_data = (char *) malloc(2*sizeof(char))) == NULL) 
    return 0;
  new_data[0] = 0;
  new_data[1] = 0;
  vector->len = 1;
  vector->full = 0;
  vector->data = new_data;
  return vector;
}

void *vector_push(Vector *vector, char ch){
  char *new_data;
  if (vector->len == vector->full){
    if ((new_data = (char *) realloc(vector->data, (vector->len*2+1)*sizeof(char))) == NULL) 
      return 0;
    new_data[vector->full] = ch;
    vector->len *= 2;
    vector->full++;
    new_data[vector->full] = 0;
    vector->data = new_data;
  }
  else{
    vector->data[vector->full] = ch;
    vector->full++;
    vector->data[vector->full] = 0;
  }
}

int compare(const void *a, const void *b){
  return ( *(char*)a - *(char*)b );
}

int wtree_is_leaf(char *abc){
  if (strlen(abc) == 1) return 1;
  else return 0;
}

Atom *wtree_generate(char *node_abc){
  char *half1, *half2, *new_abc;
  Atom *root;

  root = (Atom *) malloc(sizeof(Atom));
  new_abc = (char *) malloc((strlen(node_abc) + 1) * sizeof(char));
  strcpy(new_abc,node_abc);
  root->abc = new_abc;
  if (!wtree_is_leaf(node_abc)){
    root->bitvector = bitvector_construct(100);
    half1 = (char *) malloc((strlen(node_abc)- strlen(node_abc)/2 + 1) * sizeof(char));
    half2 = (char *) malloc((strlen(node_abc)/2 + 1) * sizeof(char));
    strncpy(half1,node_abc,strlen(node_abc)- strlen(node_abc) / 2);
    half1[strlen(node_abc)- strlen(node_abc) / 2] = '\0';
    strncpy(half2,node_abc+strlen(half1),strlen(node_abc) / 2);
    half2[strlen(node_abc) / 2] = '\0';
    root->left = wtree_generate(half1);
    root->right = wtree_generate(half2);
  }
  else{
    root->left = NULL;
    root->right = NULL;
  }
  
  return root;
}

void *wtree_tostring(Atom *wtree, int depth, char **out){
  int i = 0;

  if (depth == 0) *out = (char *) malloc( (strlen(wtree->abc)+2) * sizeof(char));
  else *out = (char *) realloc(*out, (strlen(*out) + strlen(wtree->abc)+2+depth) * sizeof(char));
  
 if (!wtree_is_leaf(wtree->abc)){    
    for (i = 0; i < depth; i++) strcat(*out,"-");
    if (depth == 0) strcpy(*out,wtree->abc);
    else strcat(*out,wtree->abc);
    strcat(*out,"\n");
    wtree_tostring(wtree->left,depth+1,out);
    wtree_tostring(wtree->right,depth+1,out);
  }
  else{ 
    *out = (char *) realloc(*out, (strlen(*out) + strlen(wtree->abc)+2+depth) * sizeof(char));
    for (i = 0; i < depth; i++) strcat(*out,"-");
    strcat(*out,wtree->abc);
    strcat(*out,"\n");
  }
}

Atom *wtree_construct(char *string, int length) {
            
  int i = 0;
  char *wtree_string;
  Vector *vector = vector_construct();
  Atom *wtree;
  while (i < length){
    if (strchr(vector->data,string[i]) == NULL) {
      vector_push(vector,string[i]);
    }
    i++;      
  } 

  qsort(vector->data,vector->full,sizeof(char),compare);

  wtree = wtree_generate(vector->data);

  wtree_tostring(wtree,0,&wtree_string);
  printf("%s\n",wtree_string);   
  
  printf("%s",vector->data); 
  system("PAUSE"); 
  return wtree; 
}

int wtree_push(Atom *wtree, char ch){
  Atom *next = wtree;
  
  while(!wtree_is_leaf(next->abc)){
    if (strchr(wtree->left->abc,ch) != NULL){
      bitvector_push(wtree->bitvector,(Bit)0);
      next = wtree->left;
    }
    else{
      bitvector_push(wtree->bitvector,(Bit)1);
      next = wtree->right;
    }
  }
}

