#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

void *global_base = NULL;

struct blockMetaInfo {
  struct blockMetaInfo *next;
  int size;
  int free;
};
typedef struct blockMetaInfo BlockMetaInfo;

#define SIZE_OF_META_BLOCK sizeof(BlockMetaInfo)

void initBlock(BlockMetaInfo *block) {
  block->next = NULL;
  block->size = 10;
  block->free = 1;
}


BlockMetaInfo *nextFreeBlock(BlockMetaInfo *last, int requestedSize) {
  struct blockMetaInfo *current = last;

  while (current) {
    printf("inside: %i\n", current->size);
    if (current->free && current->size >= requestedSize) {
      break;
    } else {
      last = current;
      current = current->next;
    }
  }

  return current;
}

// TODO: use sbrk to request space and add that space to the end of our linked list
BlockMetaInfo *requestSpace(BlockMetaInfo *last, int size){
  printf("before sbrk \n");

  BlockMetaInfo *block = sbrk(0);
  void *blockAddr = sbrk(size + SIZE_OF_META_BLOCK);

  printf("after sbrk block: %p\n", block);
  printf("after sbrk blockAddr: %p\n", blockAddr);

  if (last != NULL) {
    printf("What is last?: %p\n", last);

    last->next = block; // Segmentation fault happens here
  }

  block->size = size;
  block->free = 1;
  block->next = NULL;
  return block;
}


BlockMetaInfo *my_malloc(BlockMetaInfo *firstBlock, int blockSize) {
  BlockMetaInfo *block = nextFreeBlock(firstBlock, blockSize);

  if (block == NULL) {
    BlockMetaInfo *newSpace = requestSpace(block, blockSize);
    printf("newSpace address: %p\n", newSpace);
    printf("newSpace size: %d\n", newSpace->size);
    printf("newSpace free: %d\n", newSpace->free);
    return newSpace;
  } else {
    printf("newSpace address: %p\n", block);
    printf("newSpace size: %d\n", block->size);
    printf("newSpace free: %d\n", block->free);
    return block;
  }
}

// TODO: use the main method as simulation for first and not-first calls
//  A. To perform malloc, we first go to existing blocks (linked list) to check if there's free space
//  B. If not we want to request space and append it to the linked list
// More on sbrk (set break): https://www.cs.hmc.edu/~geoff/classes/hmc.cs134.201209/man/syscall/sbrk.html
// What's missing?
//   - How to do this without needing to pass the first block always?
//     - What about assigning a local variable 
int main(void) {
  int blockSize = 11;

  BlockMetaInfo firstBlock;
  initBlock(&firstBlock);

  printf("ITSS MEEE AGAIN, first block addr: %p\n", &firstBlock);

  my_malloc(&firstBlock, 11);
  my_malloc(&firstBlock, 12);
  my_malloc(&firstBlock, 11);

  // Ah walahy
  // printf("last's next address(should equal newSpace): %p\n", block->next);
}
