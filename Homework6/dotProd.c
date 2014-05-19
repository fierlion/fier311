#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMTHREADS 8
#define VECLEN 1000000

double SUM;

struct data{
  double *a;
  double *b;
  int veclen;
  int offset;
};

pthread_t threads[NUMTHREADS];
pthread_mutex_t mutex_SUM;  //benefits from being global because can't make 
                            //a copy of a mutex.

void *dotprod(void *arg){
  int start;
  int end;
  int length;
  double *x;
  double *y;

  double sub_SUM;


  struct data *d = (struct data*)arg;  //cast input to be correct type
  length = d->veclen;
  start = d->offset * length;
  end = start + length;
  x = d->a;
  y = d->b;

  sub_SUM = 0.0;

  for (int i=start; i < end; ++i)
    sub_SUM += x[i] * y[i];          //if just SUM then the total will be off

  pthread_mutex_lock(&mutex_SUM);  //here's the CRITICAL SECT we lock our mutex
                                   //and contribute sub_SUM to the whole
  SUM += sub_SUM;
  printf("Thread %d did %d to %d; sub sum = %f, global sum =%f",
	 d->offset, start, end, sub_SUM, SUM);
  pthread_mutex_unlock(&mutex_SUM);  //as soon as it is unlocked then one of the
                                     //threads in arbitrary order wakes and gets
                                     //the next lock until all have moved through
                                     //CRITICAL SECT

  pthread_exit((void*)0);

}

int main(int argc, char **argv){
  //create our arrays
  double *a = (double*)malloc(NUMTHREADS * VECLEN * sizeof(double));
  double *b = (double*)malloc(NUMTHREADS * VECLEN * sizeof(double));

  struct data d[NUMTHREADS];   //array of structs
  pthread_attr_t attr;         //to set the attachment state of the threads

  for(int i = 0; i< VECLEN * NUMTHREADS; ++i){
    a[i] = b[i] = 1.0;
  }

  SUM = 0.0;

  pthread_mutex_init(&mutex_SUM, NULL);  //or use attr for second arg

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < NUMTHREADS; ++i){
    d[i].a = a;
    d[i].b = b;
    d[i].offset = i;
    d[i].veclen = VECLEN;
    pthread_create(&threads[i], &attr, dotprod, (void*)&d[i]);
  }

  //clean up our mess
  pthread_attr_destroy(&attr);

  for(int i = 0; i < NUMTHREADS; ++i){
    pthread_join(threads[i], NULL); //null means we dont care about exitstatus
  }

  printf("Sum = %f\n", SUM);
  free(a);                      //free memory otherwise memory leak
  free(b);
  pthread_mutex_destroy(&mutex_SUM);

  return 0;
}
