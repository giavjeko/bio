#include <stdlib.h>
#include <string.h>

typedef struct QElement QElement;
struct QElement {
  int begin;
  int end;
  int l;
  QElement* next;
  QElement* previous;
};

typedef struct Queue Queue;
struct Queue {
  QElement* head;
  QElement* tail;
  int length;
};

QElement* queue_construct_element(int begin, int end, int l) {
  QElement* element = (QElement*)malloc(sizeof(QElement));
  element->begin = begin;
  element->end = end;
  element->l = l;
  element->next = NULL;
  element->previous = NULL;
  return element;
}

Queue* queue_construct() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;
  return queue;
}

int queue_empty(Queue* queue) {
  return ! queue->length;
}

void queue_push(Queue* queue, int begin, int end, int l) {
  QElement* element = queue_construct_element(begin, end, l);
  element->next = queue->head;
  if (queue_empty(queue)) {
    queue->tail = element;
  } else {
    queue->head->previous = element;
  }
  queue->head = element;
  queue->length++;
}

int queue_pop(Queue* queue, int* begin, int* end, int* l) {
  if (queue_empty(queue)) return 0;
  *begin = queue->tail->begin;
  *end = queue->tail->end;
  *l = queue->tail->l;
  QElement* new_tail = queue->tail->previous;
  free(queue->tail);
  queue->tail = new_tail;
  queue->length--;
  if (! queue_empty(queue)) {
    queue->tail->next = NULL;
  } else {
    queue->head = NULL;
  }
  return 1;
}

char* queue_int_tostring(int number) {
  int length, temp = number;
  if (! number) {
    return "0";
  }
  for (length = 0; temp; temp /= 10) {
    length++;
  }
  char* result = (char*)malloc((length + 1) * sizeof(char));
  int i;
  for (i = length; number; number /= 10) {
    result[--i] = (char)('0' + number % 10);
  }
  result[length] = 0;
  return result;
}

char* queue_element_tostring(QElement* element) {
  char* begin = queue_int_tostring(element->begin);
  char* end = queue_int_tostring(element->end);
  char* l = queue_int_tostring(element->l);
  int len = strlen(begin) + strlen(end) + strlen(l) + 9;
  char* result = (char*)malloc(len * sizeof(char));
  strcpy(result, "(<");
  strcat(result, begin);
  strcat(result, ", ");
  strcat(result, end);
  strcat(result, ">, ");
  strcat(result, l);
  strcat(result, ")");
  return result;
}

char* queue_tostring(Queue *queue) {
  if (queue_empty(queue)) {
    return "Empty queue";
  }
  int len = 8;
  char* result = (char*)malloc(len * sizeof(char));
  strcpy(result, "Queue: ");
  QElement* element;
  for (element = queue->head; element; element = element->next) {
    char* element_str = queue_element_tostring(element);
    len += strlen(element_str) + 2;
    result = (char*)realloc(result, len * sizeof(char));
    strcat(result, element_str);
    free(element_str);
    if (element->next) {
      strcat(result, ", ");
    }
  }
  return result;
}
