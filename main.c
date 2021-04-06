#include "common.h"
#include "chunk.h"
#include "debug.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);
  writeChunk(&chunk, OP_NO_RETURN);
  // printChunk(&chunk);
  disassembleChunk(&chunk, "Oh Chunk!");
  freeChunk(&chunk);

  return 0;
}
