#include <stdlib.h>
#include <stdio.h>
#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
  chunk->counter = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte) {
  if (chunk->counter + 1 > chunk->capacity) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  // TODO understand this whole pointer accessing through [] and how we allocate memory with capacity
  chunk->code[chunk->counter] = byte;
  chunk->counter++;
}

// Adds a value to the constants belonging to this chunk and returns index of last added value
int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.counter - 1;
}

// my attempt in printing chunks myself. TODO: Remove later
void printChunk(Chunk* chunk) {
  int i;

  printf("---- Beginning of chunk\n");
  for (i = 0; i < chunk->counter; ++i) {
    uint8_t *pntr = chunk->code + i;
    printf("address: %p\n",pntr);
    printf("value: %i\n",*pntr);
    printf("\n");
  }
  printf("---- End of chunk\n\n");
}
