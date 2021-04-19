#ifndef the_vm_vm_h
#define the_vm_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
  uint8_t* ip;   // Instruction Pointer; Same as PC (programm counter)
  Value stack[STACK_MAX];
  Value* stackTop;
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

Value pop();
void push(Value value);

#endif
