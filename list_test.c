#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "list.c"

void test_list_element_construct() {
  Element* element = list_element_construct(1, 2);
  assert(element->begin == 1);
  assert(element->end == 2);
  printf("List element construct OK\n");
}

void test_list_construct() {
  List* list = list_construct();
  assert(list->length == 0);
  assert(list_empty(list));
  printf("List construct OK\n");
}

void test_list_push() {
  List* list = list_construct();
  assert(list_empty(list));
  list_push(list, 1, 2);
  assert(list->length == 1);
  assert(list->head->begin == 1);
  assert(list->head->end == 2);
  assert(list->head == list->tail);
  assert(! list_empty(list));
  list_push(list, 3, 4);
  assert(list->length == 2);
  assert(list->head->begin == 1);
  assert(list->head->end == 2);
  assert(list->tail->begin == 3);
  assert(list->tail->end == 4);
  assert(list->head->next == list->tail);
  printf("List push OK\n");
}

void test_list_tostring() {
}

int main(void) {
  printf("List module tests running\n");
  test_list_element_construct();
  test_list_construct();
  test_list_push();
  test_list_tostring();
  printf("List module all tests passed\n");
  return 0;
}
