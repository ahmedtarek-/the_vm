#include <stdio.h>
#include "debug.h"
#include "common.h"

int simpleInstruction(char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

int constantInstruction(char* name, Chunk* chunk, int offset) {
  uint8_t constantLoc = chunk->code[offset + 1];
  Value constantValue = chunk->constants.values[constantLoc];
  printf("%-16s %4f\n", name, (double) constantValue);
  return offset + 2;
}

int binaryInstruction(char* name, Chunk* chunk, int offset) {
  uint8_t constantOneLoc = chunk->code[offset + 1];
  uint8_t constantTwoLoc = chunk->code[offset + 2];
  Value constantOne = chunk->constants.values[constantOneLoc];
  Value constantTwo = chunk->constants.values[constantTwoLoc];
  printf("%-16s %4f %4f\n", name, (double) constantOne, (double) constantTwo);

  return offset + 3;
}

void disassembleChunk(Chunk* chunk, char* name) {
  printf("-- %s --\n", name);

  for (int offset = 0; offset < chunk->counter;) {
    offset = disassembleInstruction(chunk, offset);
  }
  printf("----\n");
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
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_NO_RETURN:
      return simpleInstruction("OP_NO_RETURN", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULT:
      return simpleInstruction("OP_MULT", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
