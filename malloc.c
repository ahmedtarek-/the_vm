#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

void *global_base = NULL;

struct blockMetaInfo {
  struct blockMetaInfo *next;
  int size;
  int free;
};

typedef struct blockMetaInfo BlockMetaInfo;

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
BlockMetaInfo *requestSpace(int size){

}


// TODO: use the main method as simulation for first and not-first calls
int main(void) {
  BlockMetaInfo block_1;
  BlockMetaInfo block_2;
  BlockMetaInfo block_3;

  initBlock(&block_1);
  initBlock(&block_2);
  initBlock(&block_3);

  block_1.next = &block_2;
  block_2.next = &block_3;

  block_2.size = 20;

  printf("block_1: %p, %i\n", &block_1, block_1.size);
  printf("block_2: %p, %i\n", &block_2, block_2.size);
  printf("block_2: %p, %i\n", &block_3, block_3.size);

  printf("next free %p\n", nextFreeBlock(&block_1, 20)); 

  // printf("block_1 next: %p\n", block_1.next);
}
