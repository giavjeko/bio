#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "queue.c"

void test_queue_construct_element() {
  QElement* element = queue_construct_element(1, 2, 3);
  assert(element->begin == 1);
  assert(element->end == 2);
  assert(element->l == 3);
  assert(element->next == NULL);
  assert(element->previous == NULL);
  printf("\tQueue construct element test passed\n");
}

void test_queue_construct() {
  Queue* queue = queue_construct();
  assert(queue->head == NULL);
  assert(queue->tail == NULL);
  assert(queue->length == 0);
  printf("\tQueue construct test passed\n");
}

void test_queue_push() {
  Queue* queue = queue_construct();
  assert(queue_empty(queue));
  queue_push(queue, 1, 2, 3);
  assert(! queue_empty(queue));
  assert(queue->head->begin == 1);
  assert(queue->head->end == 2);
  assert(queue->head->l == 3);
  assert(queue->tail == queue->head);
  assert(queue->length == 1);
  QElement* old_head = queue->head;
  queue_push(queue, 4, 5, 6);
  assert(queue->head->begin == 4);
  assert(queue->head->end == 5);
  assert(queue->head->l == 6);
  assert(queue->head->next == queue->tail);
  assert(queue->tail->previous == queue->head);
  assert(queue->tail == old_head);
  assert(queue->length == 2);
  printf("\tQueue push test passed\n");
}

void test_queue_pop() {
  Queue* queue = queue_construct();
  queue_push(queue, 4, 5, 6);
  queue_push(queue, 1, 2, 3);
  int begin, end, l, return_value;
  return_value = queue_pop(queue, &begin, &end, &l);
  assert(begin == 4);
  assert(end == 5);
  assert(l == 6);
  assert(queue->length == 1);
  assert(return_value == 1);
  return_value = queue_pop(queue, &begin, &end, &l);
  assert(begin == 1);
  assert(end == 2);
  assert(l == 3);
  assert(queue->length == 0);
  assert(return_value == 1);
  return_value = queue_pop(queue, &begin, &end, &l);
  assert(return_value == 0);
  assert(queue_empty(queue));
  printf("\tQueue pop test passed\n");
}

void test_queue_element_tostring() {
  QElement* element;
  char* element_str;
  element = queue_construct_element(1, 2, 3);
  element_str = queue_element_tostring(element);
  assert(! strcmp(element_str, "(<1, 2>, 3)"));
  element = queue_construct_element(10, 452, 0);
  element_str = queue_element_tostring(element);
  assert(! strcmp(element_str, "(<10, 452>, 0)"));
  printf("\tQueue element tostring test passed\n");
}

void test_queue_tostring() {
  char* queue_str;
  Queue* queue = queue_construct();
  queue_str = queue_tostring(queue);
  assert(! strcmp(queue_str, "Empty queue"));
  queue_push(queue, 1, 2, 3);
  queue_str = queue_tostring(queue);
  assert(! strcmp(queue_str, "Queue: (<1, 2>, 3)"));
  queue_push(queue, 10, 452, 0);
  queue_str = queue_tostring(queue);
  assert(! strcmp(queue_str, "Queue: (<10, 452>, 0), (<1, 2>, 3)"));
  printf("\tQueue tostring test passed\n");
}

int main(void) {
  printf("Queue module running tests\n");
  test_queue_construct_element();
  test_queue_construct();
  test_queue_push();
  test_queue_pop();
  test_queue_element_tostring();
  test_queue_tostring();
  printf("Queue module tests passed\n");
}
