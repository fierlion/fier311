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

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct arg_struct {
  unsigned int *array;
  int numthred;
  int thredin;
  unsigned int total;
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

void * threadFunc(void *arguments){
  struct arg_struct *args = arguments;
  int i, s;
  for (i = 2; i < args->total; i++){
    if (i % args->numthred == args->thredin){
      s = pthread_mutex_lock(&mtx);
      if (s != 0){
	perror("mutex not locked");
	exit(EXIT_FAILURE);
      }
      multiples(args->array, i, args->total);
      s = pthread_mutex_unlock(&mtx);
      if (s != 0){
	perror("mutex not unlocked");
	exit(EXIT_FAILURE);
      }
    }
  }
  return NULL;
}

int main(int argc, char **argv){
  int c;
  int print = 1;
  extern char *optarg;
  extern int optind, optopt;
  unsigned int totbits = 60;
  int numthred = 2;
  unsigned int *bitArray;
  unsigned int size = ((totbits / 32)) + 1;
  int i;
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

  //make and initialize threads
    pthread_t thread[numthred];
    struct arg_struct args[numthred];
  for(i = 0; i < numthred; i++){
    int s;
    args[i].array = bitArray;
    args[i].numthred = numthred;
    args[i].thredin = i;
    args[i].total = totbits;
    //    s = pthread_create(&thread[i], NULL, threadFunc, (void *)&args[i]);
    //if (s != 0){
    //  perror("thread create error");
    //  exit(EXIT_FAILURE);
    //}
    printf("array args: %d, %d, %d, %d\n", args[i].array, args[i].numthred,
	   args[i].thredin, args[i].total);
  }

  //  for (i = 0; i < numthred; i++)
  //  pthread_join(thread[i], NULL);

  if (print > 0){
    for (i = 4; i < totbits; i++){
      if ((testBit(bitArray, i - 2) == 0) && (testBit(bitArray, i) == 0)){
	printf("%d, %d\n", i-2, i);
      }
    }
  }

  exit(EXIT_SUCCESS);
}
