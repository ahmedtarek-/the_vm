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

VMResult run(){
  printf("Inside RUN\n");
#define READ_BYTE() (*vm.ip++)
  printf("  -- chunk(addr): %p\n", vm.chunk->code);

  for (;;) {
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      printf("  -- ip: %p\n", vm.ip);
      printf(" -- Instruction: %i\n", instruction);
      case OP_RETURN:
        return RESULT_OK;
    }
  }
#undef READ_BYTE
}
