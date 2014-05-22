#define _BSD_SOURCE

#include <getopt.h>
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

void multiples(unsigned int *array, unsigned int base, unsigned int total){
  if ((base == 0) || (base == 1)){
    return;
  } else {
    for (int i = base + 1; i < total; i++){
      if (testBit(array, i) == 0){
	if (i % base == 0){
	  setBit(array, i);
	}
      }
    }
  }
}

int main(int argc, char **argv){
  int c;
  int print = 1;
  extern char *optarg;
  extern int optind, optopt;
  unsigned int totbits = UINT_MAX;          //upto UINT_MAX
  int children = 1;
  unsigned int *bitArray;
  unsigned int size = ((totbits / 32)) + 1;
  int i, j;
  int objectSize = 1024 * 1024 * 600;
  void *addr = mount_shmem("/footerPrime", objectSize);
  bitArray = malloc((sizeof(unsigned int)) * size);
  bitArray = (unsigned int*)addr;

  //getopts for children/totbits/quiet
  while ((c = getopt(argc, argv, "m:c:q")) != -1) {
    switch (c){
    case 'm':
      totbits = atol(optarg);
      break;
    case 'c':
      children = atoi(optarg);
      break;
    case 'q':
      print = 0;
      break;
    }
  }
  //initialize bit array
  for (i = 0; i < size; i++){
    bitArray[i]= 0;              
  }

  for (i = 0; i < children; i++){
    switch (fork()) {
    case -1:
      printf("fork %i failed", i);
      exit(EXIT_FAILURE);
    case 0:
      //child case
      for(j = 2; j < totbits; j++){
	if (j % children == i){
	  multiples(bitArray, j, totbits);
	}
      }
      exit(EXIT_SUCCESS);
    default:
      break;
    }
  }
  for (i = 0; i < children; i++){
    wait(NULL);
  }
  if (print > 0){
    for (i = 4; i < totbits; i++){
      if ((testBit(bitArray, i - 2) == 0) && (testBit(bitArray, i) == 0)){
	printf("%d, %d\n", i-2, i);
      }
    }
  }
  if(shm_unlink("/footerPrime") == -1)
    printf("not unlinked\n");
  exit(EXIT_SUCCESS);
}

//to divide ordered list into children n number blocks
      //      for (j = (i*blocksize); j < ((i+1) * blocksize); j++){
      //	unsigned int k = j - blocksize;
	//printf("%i ", k);
      //	multiples(bitArray, k, totbits);
      //      }
