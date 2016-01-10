#include <stdlib.h>
#include <string.h>

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
  element->next = NULL;
  return element;
}

List* list_construct() {
  List* list = (List*)malloc(sizeof(List));
  list->length = 0;
  list->head = NULL;
  list->tail = NULL;
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

char* list_int_tostring(int number) {
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

char* list_element_tostring(Element* element) {
  char* begin = list_int_tostring(element->begin);
  char* end = list_int_tostring(element->end);
  int length = strlen(begin) + strlen(end) + 5;
  char* result = (char*)malloc(length * sizeof(char));
  strcpy(result, "<");
  strcat(result, begin);
  strcat(result, ", ");
  strcat(result, end);
  strcat(result, ">");
  free(begin);
  free(end);
  return result;
}

char* list_tostring(List* list) {
  int len = 7;
  if (list_empty(list)) {
    return "Empty list";
  }
  char* result = (char*)malloc(len * sizeof(char));
  strcpy(result, "List: ");
  Element* element;
  for (element = list->head; element; element = element->next) {
    char* element_str = list_element_tostring(element);
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
