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

void *print_down(void *arg){
  struct data *d = (struct data*)arg;
  unsigned long max = d->max;  //because it's a pointer we use arrow rather than dot
  int thread_id = d->thread_id;

  for (long i = max; i>= 0; --i)
    printf("Thread %d: %ld\n", thread_id, i); 

  return NULL;
}


int main(int argc, char **argv){
  srand(time(NULL));
  struct data d[10];
  pthread_t thread[10];

  for (int i = 0; i < 10; ++i){
    d[i].max = rand() % 25;
    printf("rand=%ul\n", d[i].max);
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
