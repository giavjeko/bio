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

void test_wtree_generate() {
  Atom *root;
 
  root = wtree_generate("abc");
  assert(!strcmp(root->abc,"abc"));
  assert(!strcmp(root->left->abc,"ab"));
  assert(!strcmp(root->left->left->abc,"a"));
  assert(!strcmp(root->left->right->abc,"b"));
  assert(root->left->left->left==NULL);
  assert(root->left->left->right==NULL);
  assert(!strcmp(root->right->abc,"c"));
  assert(root->right->left==NULL);
  assert(root->right->right==NULL);
             
  root = wtree_generate("abcgmz");
  assert(!strcmp(root->abc,"abcgmz"));
  assert(!strcmp(root->left->abc,"abc"));
  assert(!strcmp(root->left->left->abc,"ab"));
  assert(!strcmp(root->left->right->abc,"c"));
  assert(root->left->left->left->left==NULL);
  assert(root->left->left->left->right==NULL);
  assert(root->left->left->right->right==NULL);
  assert(!strcmp(root->right->left->abc,"gm"));
  assert(!strcmp(root->right->right->abc,"z"));
  assert(root->right->left->left->right==NULL);
  assert(root->right->left->right->right==NULL);
  assert(root->right->right->right==NULL);

  root = wtree_generate("1");
  assert(!strcmp(root->abc,"1"));
  assert(root->left==NULL);
  assert(root->right==NULL);
  
  root = wtree_generate(" %/$");
  assert(!strcmp(root->abc," %/$"));
  assert(!strcmp(root->left->abc," %"));
  assert(!strcmp(root->right->abc,"/$"));
  assert(root->left->left->left==NULL);
  assert(root->right->right->left==NULL);

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
  test_wtree_generate();
  test_wtree_tostring();
  test_wtree_push();
  printf("Wtree module all tests passed\n");
  system("PAUSE");
  return 0;
}
