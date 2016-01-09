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
  char *alphabet = "abcde";
  Atom* wtree;

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

  wtree = wtree_construct("abc");
  assert(!strcmp(wtree->abc,"abc"));
  assert(!strcmp(wtree->left->abc,"ab"));
  assert(!strcmp(wtree->left->left->abc,"a"));
  assert(!strcmp(wtree->left->right->abc,"b"));
  assert(wtree->left->left->left==NULL);
  assert(wtree->left->left->right==NULL);
  assert(!strcmp(wtree->right->abc,"c"));
  assert(wtree->right->left==NULL);
  assert(wtree->right->right==NULL);

  wtree = wtree_construct("abcgmz");
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

  wtree = wtree_construct("1");
  assert(!strcmp(wtree->abc,"1"));
  assert(wtree->left==NULL);
  assert(wtree->right==NULL);

  wtree = wtree_construct(" %/$");
  assert(!strcmp(wtree->abc," %/$"));
  assert(!strcmp(wtree->left->abc," %"));
  assert(!strcmp(wtree->right->abc,"/$"));
  assert(wtree->left->left->left==NULL);
  assert(wtree->right->right->left==NULL);

  printf("\twtree_generate test passed\n");
}

void test_wtree_tostring() {
  Atom *root;
  char *tmp;

  root = wtree_generate("a");
  wtree_tostring(root,0,&tmp);
  assert(!strcmp(tmp,"a\n"));

  root = wtree_generate("ab");
  wtree_tostring(root,0,&tmp);
  assert(!strcmp(tmp,"ab\n-a\n-b\n"));

  root = wtree_generate("agv");
  wtree_tostring(root,0,&tmp);
  assert(!strcmp(tmp,"agv\n-ag\n--a\n--g\n-v\n"));

  root = wtree_generate("abcgimz");
  wtree_tostring(root,0,&tmp);
  assert(!strcmp(tmp,"abcgimz\n-abcg\n--ab\n---a\n---b\n--cg\n---c\n---g\n-imz\n--im\n---i\n---m\n--z\n"));

}

void test_wtree_push() {
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
