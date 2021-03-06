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
  assert(!strcmp(wtree->alphabet, "abcde"));
  assert(!strcmp(wtree->root->alphabet, "abcde"));
  assert(!strcmp(wtree->root->left->alphabet, "abc"));
  assert(!strcmp(wtree->root->left->left->alphabet, "ab"));
  assert(!strcmp(wtree->root->left->left->left->alphabet, "a"));
  assert(!strcmp(wtree->root->left->left->right->alphabet, "b"));
  assert(!strcmp(wtree->root->left->right->alphabet, "c"));
  assert(!strcmp(wtree->root->right->alphabet, "de"));
  assert(!strcmp(wtree->root->right->left->alphabet, "d"));
  assert(!strcmp(wtree->root->right->right->alphabet, "e"));
  assert(wtree_node_isleaf(wtree->root->left->left->left));
  assert(wtree_node_isleaf(wtree->root->left->left->right));
  assert(wtree_node_isleaf(wtree->root->right->left));
  assert(wtree_node_isleaf(wtree->root->right->right));
  assert(wtree->char_rank_len == 5);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 0);
  assert(wtree->char_rank[2] == 0);
  assert(wtree->char_rank[3] == 0);
  assert(wtree->char_rank[4] == 0);

  alphabet="abc";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->alphabet,"abc"));
  assert(!strcmp(wtree->root->alphabet,"abc"));
  assert(!strcmp(wtree->root->left->alphabet,"ab"));
  assert(!strcmp(wtree->root->left->left->alphabet,"a"));
  assert(!strcmp(wtree->root->left->right->alphabet,"b"));
  assert(wtree->root->left->left->left==NULL);
  assert(wtree->root->left->left->right==NULL);
  assert(!strcmp(wtree->root->right->alphabet,"c"));
  assert(wtree->root->right->left==NULL);
  assert(wtree->root->right->right==NULL);
  assert(wtree->char_rank_len == 3);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 0);
  assert(wtree->char_rank[2] == 0);

  alphabet="abcgmz";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->alphabet,"abcgmz"));
  assert(!strcmp(wtree->root->alphabet,"abcgmz"));
  assert(!strcmp(wtree->root->left->alphabet,"abc"));
  assert(!strcmp(wtree->root->left->left->alphabet,"ab"));
  assert(!strcmp(wtree->root->left->right->alphabet,"c"));
  assert(wtree->root->left->left->left->left==NULL);
  assert(wtree->root->left->left->left->right==NULL);
  assert(wtree->root->left->left->right->right==NULL);
  assert(!strcmp(wtree->root->right->left->alphabet,"gm"));
  assert(!strcmp(wtree->root->right->right->alphabet,"z"));
  assert(wtree->root->right->left->left->right==NULL);
  assert(wtree->root->right->left->right->right==NULL);
  assert(wtree->root->right->right->right==NULL);
  assert(wtree->char_rank_len == 6);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 0);
  assert(wtree->char_rank[2] == 0);
  assert(wtree->char_rank[3] == 0);
  assert(wtree->char_rank[4] == 0);
  assert(wtree->char_rank[5] == 0);

  alphabet="1";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->alphabet,"1"));
  assert(!strcmp(wtree->root->alphabet,"1"));
  assert(wtree->root->left==NULL);
  assert(wtree->root->right==NULL);
  assert(wtree->char_rank_len == 1);
  assert(wtree->char_rank[0] == 0);

  alphabet=" %/$";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  assert(!strcmp(wtree->alphabet," %/$"));
  assert(!strcmp(wtree->root->alphabet," %/$"));
  assert(!strcmp(wtree->root->left->alphabet," %"));
  assert(!strcmp(wtree->root->right->alphabet,"/$"));
  assert(wtree->root->left->left->left==NULL);
  assert(wtree->root->right->right->left==NULL);
  assert(wtree->char_rank_len == 4);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 0);
  assert(wtree->char_rank[2] == 0);
  assert(wtree->char_rank[3] == 0);

  printf("\twtree_construct test passed\n");
}

void test_wtree_tostring() {
  Wtree *wtree;
  char *tmp, *alphabet;

  alphabet="a";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"1 - 0\na\n"));

  alphabet="ab";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"2 - 0 0\nab_\n-a\n-b\n"));

  alphabet="agv";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  assert(!strcmp(tmp,"3 - 0 0 0\nagv_\n-ag_\n--a\n--g\n-v\n"));

  alphabet="abcgimz";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  tmp = wtree_tostring(wtree);
  //printf("!%s!",tmp);
  assert(!strcmp(tmp,"7 - 0 0 0 0 0 0 0\nabcgimz_\n-abcg_\n--ab_\n---a\n---b\n--cg_\n---c\n---g\n-imz_\n--im_\n---i\n---m\n--z\n"));

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
  assert(wtree->char_rank_len == 4);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 4);
  assert(wtree->char_rank[2] == 7);
  assert(wtree->char_rank[3] == 10);

  alphabet = "$_aelnp";
  string = "nle_pl$nnlleee_eaae";
  wtree = wtree_construct(alphabet, strlen(alphabet));
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  char* tmp = wtree_tostring(wtree);
  string = "7 - 0 1 3 5 11 15 18\n$_aelnp_1100110111100000000\n-$_ae_10011101111\n--$__101\n---$\n---_\n--ae_11111001\n---a\n---e\n-lnp_00100000\n--ln_1001100\n---l\n---n\n--p\n";
  assert(!strcmp(tmp,string));
  assert(! strcmp(bitvector_tostring(wtree->root->bitvector), "1100110111100000000"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->bitvector), "10011101111"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->left->bitvector), "101"));
  assert(! strcmp(bitvector_tostring(wtree->root->left->right->bitvector), "11111001"));
  assert(! strcmp(bitvector_tostring(wtree->root->right->bitvector), "00100000"));
  assert(! strcmp(bitvector_tostring(wtree->root->right->left->bitvector), "1001100"));
  assert(wtree->char_rank_len == 7);
  assert(wtree->char_rank[0] == 0);
  assert(wtree->char_rank[1] == 1);
  assert(wtree->char_rank[2] == 3);
  assert(wtree->char_rank[3] == 5);
  assert(wtree->char_rank[4] == 11);
  assert(wtree->char_rank[5] == 15);
  assert(wtree->char_rank[6] == 18);

  printf("\twtree_push test passed\n");
}

void test_wtree_get_intervals() {
  char* alphabet = "$_aelnp";
  Wtree* wtree = wtree_construct(alphabet, strlen(alphabet));
  char* string = "nle_pl$nnlleee_eaae";
  int i;
  for (i = 0; i < strlen(string); i++) {
    wtree_push(wtree, string[i]);
  }
  List* list = wtree_get_intervals(wtree,1,19);
  assert(! strcmp("List: <1, 1>, <2, 3>, <4, 5>, <6, 11>, <12, 15>, <16, 18>, <19, 19>",list_tostring(list)));
  printf("\twtree_get_intervals test passed\n");
}

int main(void) {
  printf("Wtree module running tests\n");
  test_wtree_compare();
  test_wtree_construct();
  test_wtree_tostring();
  test_wtree_push();
  test_wtree_get_intervals();
  printf("Wtree module all tests passed\n");
  return 0;
}
