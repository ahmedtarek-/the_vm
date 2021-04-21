#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

void resetStack() {
  vm.stackTop = vm.stack;
}

void initVM() {
  resetStack();
}

void freeVM() {
}

VMResult interpret(Chunk* chunk){
  vm.chunk = chunk;
  vm.ip = chunk->code;
  return run();
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

void printStackTop() {
  double value = (double) *(vm.stackTop - 1);
  printf("Stack Top: %f\n\n", value);
}


// This where magic happens (i.e bytecode dispatch)
// Switch dispatching as we see here isn't optimal but since
//  it's implementation in ANSI standard C, it's very portable
//  and actually JS and Python interpreters use this type of dispatching.
// Other types: Direct Call Threading, Direct threading and Ccomputed go-to.
VMResult run(){
  #define READ_BYTE() (*vm.ip++)
  #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
  #define BINARY_OP(op) \
    do { \
      Value firstValue = pop(); \
      Value secondValue = pop(); \
      push(firstValue op secondValue); \
      printStackTop(); \
    } while (false)

    printf("Enter RUN\n");
    for (;;) {
      disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
      uint8_t instruction;

      switch (instruction = READ_BYTE()) {
        case OP_RETURN: {
          return RESULT_OK;
        }
        case OP_CONSTANT: { 
         Value constant = READ_CONSTANT();
         push(constant);
         printStackTop();
         break;
        }
        case OP_NEGATE: {
          Value negatedValue = pop() * -1;
          push(negatedValue);
          printStackTop();
          break;
        }
        case OP_ADD: {
          BINARY_OP(+);
          break;
        }
        case OP_SUBTRACT: {
          BINARY_OP(-);
          break;
        }
        case OP_MULT: {
          BINARY_OP(*);
          break;
        }
        case OP_DIVIDE: {
          BINARY_OP(/);
          break;
        }
      }
    }
    printf("Exit RUN\n");

  #undef READ_BYTE
  #undef READ_CONSTANT
}
