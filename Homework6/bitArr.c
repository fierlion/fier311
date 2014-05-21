#define _BSD_SOURCE

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
    
void setBit(unsigned int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;            // flag = 0000.....000001
  flag = flag << pos;      // flag = 0000.....100000 (shifted k positions)
  a[i] = a[i] | flag;      // set the bit at the k-th position in a[i]
}

void clearBit(unsigned int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  flag = ~flag;
  a[i] = a[i] & flag;      // REset the bit at k-th position in a[i]
}

int testBit(unsigned int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  if (a[i] & flag)
    return 1;
  return 0;
}

void *mount_shmem(char *path, int object_size){
  int shmem_fd;
  void *addr;

  //open sh mem obj
  shmem_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if(shmem_fd == -1){
    fprintf(stdout, "failed to open Shared mem obj");
    exit(EXIT_FAILURE);
  }

  //once created it defaults to size 0  need ftruncate to enlarge.
  if(ftruncate(shmem_fd, object_size) == -1){
    fprintf(stdout, "failed to resized sh mem obj");
    exit(EXIT_FAILURE);
  }

  //meed to map obj to address space
  addr= mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED,
	     shmem_fd, 0);   //0 is the offset...how far in to start

  if(addr == MAP_FAILED){
    fprintf(stdout, "failed to map sh mem obj");
    exit(EXIT_FAILURE);
  }
  return addr;
}

void multiples(unsigned int *a, int base, unsigned int tbits){
  for (int i = base + 1; i < tbits; i++){
    if (i % base == 0){
      setBit(a, i);
    }
  }  
}

int main(int argc, char **argv){
  unsigned int totbits = 64;          //upto UINT_MAX
  int children = 4;
  unsigned int *bitArray;
  unsigned int size = ((totbits / 32)) + 1;
  int i, j;
  int blocksize = totbits / children;
  int objectSize = 1024 * 1024 * 600;
  //pid_t childpid;  
  void *addr = mount_shmem("/footerPrime", objectSize);
  bitArray = malloc((sizeof(unsigned int)) * size); //allocate size of unsinged int x size
  bitArray = (unsigned int*)addr;

  for (i = 0; i < size; i++){
    bitArray[i]= 0;               //initialize bit array
  }

  for (i = 1; i <= children; i++){
    switch (fork()) {
    case -1:
      printf("fork %i failed", i);
      exit(EXIT_FAILURE);
    case 0:
      //child case
      printf("child %i\n", i);
      for (j = (i*blocksize); j < ((i+1) * blocksize); j++){
	if (testBit(bitArray, j) == 0){
	  multiples(bitArray, j, totbits);
	}
	printf("%i ", j);
      }
      printf("\n");
      exit(EXIT_SUCCESS);
    default:
      break;
    }
  }

  for (i = 0; i < children; i++){
    wait(NULL);
  }

  for (i = 2; i < totbits; i++){
    if (testBit(bitArray, i) == 0){
      printf("%d\t", i);
    }
  }
  //  printf("\n%ui\n", UINT_MAX);
  printf("\n");
  return 0;
}

