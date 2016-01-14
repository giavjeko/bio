// Implements set structure containing chars

#include <stdlib.h>
#include <string.h>

typedef struct Set Set;
struct Set {
  int capacity;
  int size;
  char* data;
};

// Allocate memory and initialize empty set
Set* set_construct() {
  Set* set = (Set*)malloc(sizeof(Set));
  set->capacity = 1;
  set->size = 0;
  set->data = (char*)malloc(2 * sizeof(char));
  set->data[0] = 0;
  return set;
}

// Return boolean telling if given set is empty
int set_is_full(Set* set) {
  return set->capacity == set->size;
}

// Reallocate memory doubleing capacity of given set
void set_extend(Set* set) {
  set->data = (char*)realloc(set->data, (set->capacity * 2 + 1) * sizeof(char));
  set->capacity *= 2;
}

// Push given char to given set
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

// Return boolean telling if given char exists in given set
int set_contains(Set* set, char ch) {
  return strchr(set->data, ch) != NULL;
}

// Helper function used to sort string
int set_compare(const void *a, const void *b) {
  return (*(char*)a - *(char*)b);
}

// Return string representation of given set
char* set_tostring(Set* set) {
  qsort(set->data, set->size, sizeof(char), set_compare);
  return set->data;
}
