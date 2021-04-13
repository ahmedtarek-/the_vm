#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "vm.h"

VM vm;

void initVM() {

};
void freeVM() {

};

VMResult interpret(Chunk* chunk){
  vm.chunk = chunk;
  vm.ip = chunk->code;
  return run();
}

// This where magic happens (i.e bytecode dispatch)
// Switch dispatching as we see here isn't optimal but since
//  it's implementation in ANSI standard C, it's very portable
//  and actually JS and Python interpreters use this type of dispatching.
// Other types: Direct Call Threading, Direct threading and Ccomputed go-to.
VMResult run(){
  #define READ_BYTE() (*vm.ip++)
    printf("Enter RUN\n");

    for (;;) {
      uint8_t instruction;
      switch (instruction = READ_BYTE()) {
        case OP_RETURN:
          printf(" -- ip after: %p\n", vm.ip);
          printf(" -- Instruction: %i\n", instruction);
          return RESULT_OK;
      }
    }
    printf("Exit RUN\n");
  #undef READ_BYTE
}
