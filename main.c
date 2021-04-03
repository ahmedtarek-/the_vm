#include "common.h"
#include "chunk.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);
  writeChunk(&chunk, OP_NO_RETURN);
  printChunk(&chunk);
  freeChunk(&chunk);

  return 0;
}
