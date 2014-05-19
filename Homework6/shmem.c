#define _BSD_SOURCE

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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


int main(int argc, char **argv){
  unsigned char *bitmap;
  int bitmap_size = 34000000 / 8 + 1;  //represent this many numbers
                                       //divided by bits, with one just in case
  int *perfect_numbers;
  int perfect_number_count = 10;

  int object_size = 1024 * 1024 * 60;   //gives 60 megabytes

  void *addr = mount_shmem("/footer_examp", object_size);

  //everything is done relative to addr--addr is the new 0
  //BE VERY CAREFUL WITH POINTER ARITHMETIC.  IT IS RELATIVE 
  //TO THE TYPE OF THE POINTER.  TYPE CAST ALL ASSIGNMENTS.

  bitmap = (unsigned char*)addr;
  perfect_numbers = (int*)(bitmap + bitmap_size);
  //bitmap_size is number of chars in the bitmap, so this plus will move in 
  //increments of the pointer

  //perfect_numbers[0] = 6;
  //perfect_numbers[1] = 28;  
  //perfect_numbers[2] = 496;  
  //perfect_numbers[3] = 8128;  
  //perfect_numbers[4] = 33550336;

  fprintf(stdout, "%d\n%d\n%d\n%d\n%d\n",
	  perfect_numbers[0],
	  perfect_numbers[1],
	  perfect_numbers[2],
	  perfect_numbers[3],
	  perfect_numbers[4]);

  //put things that are resizeable at the end of your shared memory region
  //constants at beginning.

  exit(EXIT_SUCCESS);
}
