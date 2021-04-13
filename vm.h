#ifndef the_vm_vm_h
#define the_vm_vm_h

#include "chunk.h"

typedef struct {
  Chunk* chunk;
  uint8_t* ip;   // Instruction Pointer; Same as PC (programm counter)
} VM;

typedef enum {
  RESULT_OK,
  RESULT_COMPILE_ERROR,
  RESULT_RUNTIME_ERROR
} VMResult;

void initVM();
void freeVM();

VMResult interpret(Chunk* chunk);
VMResult run();

#endif
