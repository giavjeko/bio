#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "wtree.c"

void test_wtree_compare() {
  char a,b;
  a = 'a';
  b = 'b';
  assert(wtree_compare(&a,&a)==0);
  assert(wtree_compare(&a,&b)<0);
  assert(wtree_compare(&b,&a)>0);
  printf("\twtree_compare test passed\n");
}

void test_wtree_construct() {
  char *alphabet;
  Wtree* wtree;

  alphabet = "abcde";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->root->abc, "abcde"));
  assert(!strcmp(wtree->root->left->abc, "abc"));
  assert(!strcmp(wtree->root->left->left->abc, "ab"));
  assert(!strcmp(wtree->root->left->left->left->abc, "a"));
  assert(!strcmp(wtree->root->left->left->right->abc, "b"));
  assert(!strcmp(wtree->root->left->right->abc, "c"));
  assert(!strcmp(wtree->root->right->abc, "de"));
  assert(!strcmp(wtree->root->right->left->abc, "d"));
  assert(!strcmp(wtree->root->right->right->abc, "e"));
  assert(wtree_node_isleaf(wtree->root->left->left->left));
  assert(wtree_node_isleaf(wtree->root->left->left->right));
  assert(wtree_node_isleaf(wtree->root->right->left));
  assert(wtree_node_isleaf(wtree->root->right->right));
  assert(wtree->Clen == 5);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 0);
  assert(wtree->C[2] == 0);
  assert(wtree->C[3] == 0);
  assert(wtree->C[4] == 0);

  alphabet="abc";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->root->abc,"abc"));
  assert(!strcmp(wtree->root->left->abc,"ab"));
  assert(!strcmp(wtree->root->left->left->abc,"a"));
  assert(!strcmp(wtree->root->left->right->abc,"b"));
  assert(wtree->root->left->left->left==NULL);
  assert(wtree->root->left->left->right==NULL);
  assert(!strcmp(wtree->root->right->abc,"c"));
  assert(wtree->root->right->left==NULL);
  assert(wtree->root->right->right==NULL);
  assert(wtree->Clen == 3);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 0);
  assert(wtree->C[2] == 0);

  alphabet="abcgmz";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->root->abc,"abcgmz"));
  assert(!strcmp(wtree->root->left->abc,"abc"));
  assert(!strcmp(wtree->root->left->left->abc,"ab"));
  assert(!strcmp(wtree->root->left->right->abc,"c"));
  assert(wtree->root->left->left->left->left==NULL);
  assert(wtree->root->left->left->left->right==NULL);
  assert(wtree->root->left->left->right->right==NULL);
  assert(!strcmp(wtree->root->right->left->abc,"gm"));
  assert(!strcmp(wtree->root->right->right->abc,"z"));
  assert(wtree->root->right->left->left->right==NULL);
  assert(wtree->root->right->left->right->right==NULL);
  assert(wtree->root->right->right->right==NULL);
  assert(wtree->Clen == 6);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 0);
  assert(wtree->C[2] == 0);
  assert(wtree->C[3] == 0);
  assert(wtree->C[4] == 0);
  assert(wtree->C[5] == 0);

  alphabet="1";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->root->abc,"1"));
  assert(wtree->root->left==NULL);
  assert(wtree->root->right==NULL);
  assert(wtree->Clen == 1);
  assert(wtree->C[0] == 0);

  alphabet=" %/$";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->root->abc," %/$"));
  assert(!strcmp(wtree->root->left->abc," %"));
  assert(!strcmp(wtree->root->right->abc,"/$"));
  assert(wtree->root->left->left->left==NULL);
  assert(wtree->root->right->right->left==NULL);
  assert(wtree->Clen == 4);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 0);
  assert(wtree->C[2] == 0);
  assert(wtree->C[3] == 0);

  printf("\twtree_construct test passed\n");
}

void test_wtree_tostring() {
  Wtree *wtree;
  char *tmp, *alphabet;

  alphabet="a";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"a\n"));

  alphabet="ab";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"ab_\n-a\n-b\n"));

  alphabet="agv";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"agv_\n-ag_\n--a\n--g\n-v\n"));

  alphabet="abcgimz";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"abcgimz_\n-abcg_\n--ab_\n---a\n---b\n--cg_\n---c\n---g\n-imz_\n--im_\n---i\n---m\n--z\n"));

  printf("\twtree_tostring test passed\n");
}

void test_wtree_push() {
  char* alphabet = "abcd";
  Wtree* wtree = wtree_construct(alphabet, strlen(alphabet));
  char* string = "abdacccabbad";
  int i;
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  assert(! strcmp(bitvector_tostring(wtree->root->bitvector), "001011100001"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->bitvector), "0100110"));
  assert(! strcmp(bitvector_tostring(wtree->root->right->bitvector), "10001"));
  assert(wtree->Clen == 4);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 4);
  assert(wtree->C[2] == 7);
  assert(wtree->C[3] == 10);

  alphabet = "$_aelnp";
  string = "nle_pl$nnlleee_eaae";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  assert(! strcmp(bitvector_tostring(wtree->root->bitvector), "1100110111100000000"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->bitvector), "10011101111"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->left->bitvector), "101"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->right->bitvector), "11111001"));
  assert(! strcmp(bitvector_tostring(wtree->root->right->bitvector), "00100000"));
  assert(! strcmp(bitvector_tostring(wtree->root->right->left->bitvector), "1001100"));
  assert(wtree->Clen == 7);
  assert(wtree->C[0] == 0);
  assert(wtree->C[1] == 1);
  assert(wtree->C[2] == 3);
  assert(wtree->C[3] == 5);
  assert(wtree->C[4] == 11);
  assert(wtree->C[5] == 15);
  assert(wtree->C[6] == 18);
  
  printf("\twtree_push test passed\n");
}

void test_wtree_getIntervals() {
  char* alphabet = "$_aelnp";
  Wtree* wtree = wtree_construct(alphabet, strlen(alphabet));
  char* string = "nle_pl$nnlleee_eaae";
  int i;
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  List* list = wtree_getIntervals(wtree,1,19);
  printf("%s",list_tostring(list));
  system("PAUSE");
}

int main(void) {
  printf("Wtree module running tests\n");
  test_wtree_compare();
  test_wtree_construct();
  test_wtree_tostring();
  test_wtree_push();
  test_wtree_getIntervals();
  printf("Wtree module all tests passed\n");
  return 0;
}
