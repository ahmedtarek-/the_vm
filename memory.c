#include <stdlib.h>
#include "common.h"
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  pointer = realloc(pointer, newSize);
  return pointer;
}
