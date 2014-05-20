#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BITARSZ 1    
#define TOTBITS 32         // bitArr will hold (32 * BITARSZ) bits

void setBit(int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;            // flag = 0000.....000001
  flag = flag << pos;      // flag = 0000.....100000 (shifted k positions)
  a[i] = a[i] | flag;      // set the bit at the k-th position in a[i]
}

void clearBit(int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  flag = ~flag;
  a[i] = a[i] & flag;      // REset the bit at k-th position in a[i]
}

int testBit(int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  if (a[i] & flag)
    return 1;
  return 0;
}

void multiples(int *a, int base){
  for (int i = base + 1; i < TOTBITS; i++){
    if (i % base == 0){
      setBit(a, i);
    }
  }  
}

int main(int argc, char **argv){
  int a[BITARSZ];               // bit array = bit 0 - (32 * BITARSZ)
  int i;
  int children = 8;
  int blocksize = TOTBITS / children;
  //pid_t childpid;
  
  for (i = 0; i < BITARSZ; i++){
    a[i]= 0;               //initialize bit array
  }

  printf("blocksize = %i\n", blocksize);

  for (i = 2; i < TOTBITS; i++){
    if (testBit(a, i) == 0){
      multiples(a, i);
    }
  }

  for (i = 2; i < TOTBITS; i++){
    if (testBit(a, i) == 0){
	printf(" %d\t", i);
    }
  }
  //  printf("\n%ui\n", UINT_MAX);
  printf("\n");
  return 0;
}

