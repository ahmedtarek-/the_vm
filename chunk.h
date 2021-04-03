#ifndef the_vm_chunk_h
#define the_vm_chunk_h

#include "common.h"

typedef enum {
  OP_RETURN,
  OP_NO_RETURN,
} OpCode;

typedef struct {
  int counter;
  int capacity;
  uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void printChunk(Chunk* chunk);

#endif
