#include <stdlib.h>
#include <string.h>

typedef struct Set Set;
struct Set {
  int capacity;
  int size;
  char* data;
};

Set* set_construct(){
  Set* set = (Set*)malloc(sizeof(Set));
  set->capacity = 1;
  set->size = 0;
  set->data = (char*)malloc(2 * sizeof(char));
  set->data[0] = 0;
  return set;
}

int set_is_full(Set* set) {
  return set->capacity == set->size;
}

void set_extend(Set* set) {
  set->data = (char*)realloc(set->data, (set->capacity * 2 + 1) * sizeof(char));
  set->capacity *= 2;
}

int set_push(Set* set, char ch) {
  if (strchr(set->data, ch)) {
    return 0;
  }
  set->data[set->size++] = ch;
  set->data[set->size] = 0;
  if (set_is_full(set)) {
    set_extend(set);
  }
  return 1;
}

int set_contains(Set* set, char ch) {
  return strchr(set->data, ch) != NULL;
}

int set_compare(const void *a, const void *b) {
  return (*(char*)a - *(char*)b);
}

char* set_tostring(Set* set) {
  qsort(set->data, set->size, sizeof(char), set_compare);
  return set->data;
}
