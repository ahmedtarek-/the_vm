#include <stdio.h>
#include "debug.h"
#include "common.h"

int simpleInstruction(char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

void disassembleChunk(Chunk* chunk, char* name) {
  printf("-- %s --\n", name);

  for (int offset = 0; offset < chunk->counter;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf(" %d ", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch(instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_NO_RETURN:
      return simpleInstruction("OP_NO_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
