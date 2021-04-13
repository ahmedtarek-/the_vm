#include "common.h"
#include "chunk.h"
#include "vm.h"
#include "debug.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  Value const1 = 10.4;
  Value const2 = 32.6;
  initChunk(&chunk);

  printf("Location of %f in chunk constansts is %i\n", (double) const1 , addConstant(&chunk, const1)); 
  printf("Location of %f in chunk constansts is %i\n", (double) const2 , addConstant(&chunk, const2)); 
  // addConstant(&chunk, const1);

  writeChunk(&chunk, OP_RETURN, 123);
  writeChunk(&chunk, OP_NO_RETURN, 123);

  // printChunk(&chunk);
  disassembleChunk(&chunk, "Oh Chunk!");
  interpret(&chunk);

  freeChunk(&chunk);

  freeVM();

  return 0;
}
