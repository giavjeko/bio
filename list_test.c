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

void test_list_int_tostring() {
  char *first = list_int_tostring(12);
  assert(! strcmp(first, "12"));
  char *second = list_int_tostring(123450);
  assert(! strcmp(second, "123450"));
  printf("Int to string OK\n");
}

void test_list_element_tostring() {
  Element* element = list_element_construct(1235, 23556);
  char* string = list_element_tostring(element);
  assert(! strcmp(string, "<1235, 23556>"));
  printf("List element tostring OK\n");
}

void test_list_tostring() {
  List* list = list_construct();
  char* empty_list_str = list_tostring(list);
  assert(! strcmp(empty_list_str, "Empty list"));
  list_push(list, 1235, 23456);
  list_push(list, 888, 2934);
  char* list_str = list_tostring(list);
  assert(! strcmp(list_str, "List: <1235, 23456>, <888, 2934>"));
  printf("List tostring OK\n");
}

int main(void) {
  printf("List module tests running\n");
  test_list_element_construct();
  test_list_construct();
  test_list_push();
  test_list_int_tostring();
  test_list_element_tostring();
  test_list_tostring();
  printf("List module all tests passed\n");
  return 0;
}
