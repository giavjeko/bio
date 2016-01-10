#include <stdio.h>
#include <string.h>
#include "bwt.c"
#include "wtree.c"
#include "set.c"
#include "queue.c"

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

int* compute_LCP(Wtree* wtree) {
  int i, j, l;
  int n = wtree->root->bitvector->length;
  int* LCP = (int*)malloc((n+1)*sizeof(int));
  int ii = 0;
  Queue* queue = queue_construct();
  List* list = list_construct();
  Element* element;
  
  for (ii = 1; ii <= n+1; ii++) {
    if (ii == 1 || ii == n+1) LCP[ii] = -1;
    else LCP[ii] = -2;
  }
  
  queue_push(queue,1,n,0);
  while(!queue_empty(queue)) {
    queue_pop(queue,&i,&j,&l);
    list = wtree_getIntervals(wtree,i,j);
    for (element = list->head; element; element=element->next) {
      if (LCP[element->end+1] == -2) {
        queue_push(queue,element->begin,element->end,l+1);
        LCP[element->end+1] = l; 
      }
    }
  }

  printf("LCP:\n");  
  for (ii = 1; ii <= n+1; ii++) {
    printf("%d ",LCP[ii]);
  }
  printf("\n");
}

int main () {
  char* input = "el_anele_lepanelen$";
  char* alphabet = generate_alphabet(input, strlen(input));
  char* bwt = (char*)malloc((strlen(input) + 1) * sizeof(char));
  bwt_transform(input, bwt, strlen(input));
  Wtree* wtree = generate_wtree(bwt, strlen(input), alphabet, strlen(alphabet));
  printf("%s\n%s\n%s\n\n%s\n", input, alphabet, bwt, wtree_tostring(wtree));
  
  compute_LCP(wtree);
  system("PAUSE");
  return 0;
}
