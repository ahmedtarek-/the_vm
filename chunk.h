#ifndef the_vm_chunk_h
#define the_vm_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_RETURN,
  OP_NO_RETURN,
} OpCode;

typedef struct {
  int counter;
  int capacity;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void printChunk(Chunk* chunk);

#endif
