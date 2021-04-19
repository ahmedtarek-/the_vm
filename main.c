#include "common.h"
#include "chunk.h"
#include "vm.h"
#include "debug.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  initVM();

  // 1. Prepare chunk and constants
  Chunk chunk;
  Value const1 = 10.4;
  Value const2 = 32.6;
  Value const3 = 2.0;
  Value const4 = 1.0;
  Value const5 = 1.0;
  initChunk(&chunk);

  uint8_t const1Loc = addConstant(&chunk, const1);
  uint8_t const2Loc = addConstant(&chunk, const2);
  uint8_t const3Loc = addConstant(&chunk, const3);
  uint8_t const4Loc = addConstant(&chunk, const4);
  uint8_t const5Loc = addConstant(&chunk, const5);


  // 2. Write to chunk
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const1Loc, 123);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const2Loc, 124);

  writeChunk(&chunk, OP_NEGATE, 124);

  writeChunk(&chunk, OP_ADD, 124);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const3Loc, 123);

  writeChunk(&chunk, OP_MULT, 124);

  writeChunk(&chunk, OP_RETURN, 124);

  // 3. Debug chunk
  disassembleChunk(&chunk, "Oh Chunk!");
  
  // 4. Run chunk
  interpret(&chunk);

  // 5. Free chunk
  freeChunk(&chunk);
  freeVM();

  return 0;
}
