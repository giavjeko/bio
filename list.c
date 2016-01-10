#include "vector.c"

typedef struct Element Element;
struct Element {
  int begin, end;
  Element* next;
};

typedef struct List List;
struct List {
  Element* head;
  Element* tail;
  int length;
};

Element* list_element_construct(int begin, int end) {
  Element* element = (Element*)malloc(sizeof(Element));
  element->begin = begin;
  element->end = end;
  return element;
}

List* list_construct() {
  List* list = (List*)malloc(sizeof(List));
  list->length = 0;
  return list;
}

int list_empty(List* list) {
  return ! list->length;
}

void list_push(List* list, int begin, int end) {
  Element* element = list_element_construct(begin, end);
  if (! list_empty(list)) {
    list->tail->next = element;
  } else {
    list->head = element;
  }
  list->tail = element;
  list->length++;
}
