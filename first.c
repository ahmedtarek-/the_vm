#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

// Calculates Prime numbers between 2 and n
int sieve(int n) {
  int i, j;
  int numbersSize = ceil((n-2)/2) + 1;
  int numbers[numbersSize];
  int counter = 1;

  printf("array size: %d\n", numbersSize);

  numbers[0] = 2;
  for (i = 2; i <= n; ++i) {
    if (i % 2 == 1) {
      numbers[counter] = i;
      counter++;
    }
  }
  
  for (i = 0; i < numbersSize; ++i) {
    if (numbers[i] == -1) { continue; }
    for (j = i+1; j < numbersSize; ++j) {
      if (numbers[j] == -1) { continue; }
      if (numbers[j] % numbers[i] == 0) {
        numbers[j] = -1;
      }
    }
  }
  printf("\n");

  for (i = 0; i <= (numbersSize -1); ++i) {
    if (numbers[i] != -1) {
      printf("Prime: %i\n", numbers[i]);
    }
  }

  return 0;
}

int main(void) {
  // printf("HELLO WORLD\nWORLD, WE WILL CREATE AN ALGO THAT PRODUCES PRIME NUMBERS\n");

  printf("size of uint8_t: %lu\n", sizeof(uint8_t));
  int n = 5;

  uint8_t *code = (uint8_t*)malloc(sizeof(uint8_t) * n);

  printf("addresses&values in code:\n");
  for (int i=0; i<n; ++i) {
    uint8_t *pntr = code + i;
    *pntr = i*10;
    printf("%p\n",pntr);
    printf("%i\n",*pntr);
  }

  // sieve(44);

  return 0;
}
