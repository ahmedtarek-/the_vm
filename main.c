#include "common.h"
#include "chunk.h"
#include "vm.h"
#include "debug.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  initVM();

  // 1. Prepare chunk and constants
  Chunk chunk;
  Value const1 = 1.0;
  Value const2 = 2.0;
  Value const3 = 3.0;
  Value const4 = 4.0;
  Value const5 = 5.0;
  initChunk(&chunk);

  uint8_t const1Loc = addConstant(&chunk, const1);
  uint8_t const2Loc = addConstant(&chunk, const2);
  uint8_t const3Loc = addConstant(&chunk, const3);
  uint8_t const4Loc = addConstant(&chunk, const4);
  uint8_t const5Loc = addConstant(&chunk, const5);

  // 2. Write to chunk ( 1 + (2 * 3) - (4 / -5) )
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const5Loc, 123);

  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, const4Loc, 123);

  writeChunk(&chunk, OP_DIVIDE, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const2Loc, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const3Loc, 124);

  writeChunk(&chunk, OP_MULT, 124);

  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, const1Loc, 124);

  writeChunk(&chunk, OP_ADD, 124);

  writeChunk(&chunk, OP_SUBTRACT, 124);

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
