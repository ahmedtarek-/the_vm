#ifndef the_vm_debug
#define the_vm_debug

#include "chunk.h"

void disassembleChunk(Chunk* chunk, char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif
