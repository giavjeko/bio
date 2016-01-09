#include <string.h>
#include <stdlib.h>
#include "vector.c"
#include "bitvector.c"

typedef struct at Atom;
struct at {
  char *abc;
  Bitvector *bitvector;
  Atom *left; 
  Atom *right;
};

int compare(const void *a, const void *b){
  return ( *(char*)a - *(char*)b );
}

Atom *wtree_generate(char *node_abc){
  char *half1, *half2, *new_abc;
  Atom *root;

  root = (Atom *) malloc(sizeof(Atom));
  new_abc = (char *) malloc((strlen(node_abc) + 1) * sizeof(char));
  strcpy(new_abc,node_abc);
  root->abc = new_abc;
  if (strlen(node_abc) != 1){
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
  
 if (strlen(wtree->abc) != 1){    
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

void wtree_construct(char *string, int length) {
            
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
}

int main(){
wtree_construct("bbhfbb",6);

return 1;    
}
