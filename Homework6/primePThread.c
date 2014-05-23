//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 6 (pthreads)

#define _BSD_SOURCE

#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct data{
  unsigned long max;
  int thread_id;
};

void setBit(unsigned int a[], int k){
  int i= k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  a[i] = a[i] | flag;
}

void clearBit(unsigned int a[], int k){
  int i = k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  flag = ~flag;
  a[i] = a[i] & flag;
}

int testBit(unsigned int a[], int k){
  int i= k/32;
  int pos = k%32;
  int flag = 1;
  flag = flag << pos;
  if (a[i] & flag)
    return 1;
  return 0;
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

void *print_down(void *arg){
  struct data *d = (struct data*)arg;
  unsigned long max = d->max;  //because it's a pointer we use arrow rather than dot
  int thread_id = d->thread_id;

  for (long i = max; i>= 0; --i)
    printf("Thread %d: %ld\n", thread_id, i); 

  return NULL;
}

int main(int argc, char **argv){
  int c;
  int print = 1;
  extern char *optarg;
  extern int optind, optopt;
  unsigned int totbits = UINT_MAX;
  int numthred = 1;
  unsigned int *bitArray;
  unsigned int size = ((totbits / 32)) + 1;
  int i, j;
  bitArray = malloc((sizeof(unsigned int)) * size);
 
 //getopts for numthred/totbits/quiet
  while ((c = getopt(argc, argv, "m:c:q")) != -1) {
    switch (c){
    case 'm':
      totbits = atol(optarg);
      break;
    case 'c':
      numthred =atoi(optarg);
      break;
    case 'q':
      print = 0;
      break;
    }
  }

  //intitialize bit array
  for (i = 0; i < size; i++){
    bitArray[i] = 0;
  }

  srand(time(NULL));
  struct data d[10];
  pthread_t thread[10];

  for (int i = 0; i < 10; ++i){
    d[i].max = rand() % 25;
    printf("rand=%lui\n", d[i].max);
    d[i].thread_id = i;
    if(0 != pthread_create(&thread[i],
			   NULL,
			   print_down,
			   (void*)&d[i])){
      perror("can't create thread");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < 10; ++i)
    pthread_join(thread[i], NULL);

  return 0;
}
