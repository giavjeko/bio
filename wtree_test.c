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
  Atom* wtree;

  alphabet = "abcde";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->abc, "abcde"));
  assert(!strcmp(wtree->left->abc, "abc"));
  assert(!strcmp(wtree->left->left->abc, "ab"));
  assert(!strcmp(wtree->left->left->left->abc, "a"));
  assert(!strcmp(wtree->left->left->right->abc, "b"));
  assert(!strcmp(wtree->left->right->abc, "c"));
  assert(!strcmp(wtree->right->abc, "de"));
  assert(!strcmp(wtree->right->left->abc, "d"));
  assert(!strcmp(wtree->right->right->abc, "e"));
  assert(wtree_is_leaf(wtree->left->left->left));
  assert(wtree_is_leaf(wtree->left->left->right));
  assert(wtree_is_leaf(wtree->right->left));
  assert(wtree_is_leaf(wtree->right->right));

  alphabet="abc";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->abc,"abc"));
  assert(!strcmp(wtree->left->abc,"ab"));
  assert(!strcmp(wtree->left->left->abc,"a"));
  assert(!strcmp(wtree->left->right->abc,"b"));
  assert(wtree->left->left->left==NULL);
  assert(wtree->left->left->right==NULL);
  assert(!strcmp(wtree->right->abc,"c"));
  assert(wtree->right->left==NULL);
  assert(wtree->right->right==NULL);

  alphabet="abcgmz";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->abc,"abcgmz"));
  assert(!strcmp(wtree->left->abc,"abc"));
  assert(!strcmp(wtree->left->left->abc,"ab"));
  assert(!strcmp(wtree->left->right->abc,"c"));
  assert(wtree->left->left->left->left==NULL);
  assert(wtree->left->left->left->right==NULL);
  assert(wtree->left->left->right->right==NULL);
  assert(!strcmp(wtree->right->left->abc,"gm"));
  assert(!strcmp(wtree->right->right->abc,"z"));
  assert(wtree->right->left->left->right==NULL);
  assert(wtree->right->left->right->right==NULL);
  assert(wtree->right->right->right==NULL);

  alphabet="1";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->abc,"1"));
  assert(wtree->left==NULL);
  assert(wtree->right==NULL);

  alphabet=" %/$";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->abc," %/$"));
  assert(!strcmp(wtree->left->abc," %"));
  assert(!strcmp(wtree->right->abc,"/$"));
  assert(wtree->left->left->left==NULL);
  assert(wtree->right->right->left==NULL);

  printf("\twtree_construct test passed\n");
}

void test_wtree_tostring() {
  Atom *wtree;
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
  Atom* wtree = wtree_construct(alphabet, strlen(alphabet));
  char* string = "abdacccabbad";
  int i;
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  assert(! strcmp(bitvector_tostring(wtree->bitvector), "001011100001"));
  assert(! strcmp(bitvector_tostring(wtree->left->bitvector), "0100110"));
  assert(! strcmp(bitvector_tostring(wtree->right->bitvector), "10001"));

  alphabet = "$_aelnp";
  string = "nle_pl$nnlleee_eaae";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  assert(! strcmp(bitvector_tostring(wtree->bitvector), "1100110111100000000"));
  assert(! strcmp(bitvector_tostring(wtree->left->bitvector), "10011101111"));
  assert(! strcmp(bitvector_tostring(wtree->left->left->bitvector), "101"));
  assert(! strcmp(bitvector_tostring(wtree->left->right->bitvector), "11111001"));
  assert(! strcmp(bitvector_tostring(wtree->right->bitvector), "00100000"));
  assert(! strcmp(bitvector_tostring(wtree->right->left->bitvector), "1001100"));

  printf("\twtree_push test passed\n");
}

int main(void) {
  printf("Wtree module running tests\n");
  test_wtree_compare();
  test_wtree_construct();
  test_wtree_tostring();
  test_wtree_push();
  printf("Wtree module all tests passed\n");
  system("PAUSE");
  return 0;
}
