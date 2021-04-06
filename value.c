#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "memory.h"

void initValueArray(ValueArray* array) {
  array->counter = 0;
  array->capacity = 0;
  array->values = NULL;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void writeValueArray(ValueArray* array, Value value) {
  if (array->counter + 1 > array->capacity) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
  }

  // TODO understand this whole pointer accessing through [] and how we allocate memory with capacity
  array->values[array->counter] = value;
  array->counter++;
}
