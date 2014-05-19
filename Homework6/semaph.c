#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv){
  sem_t *sem = sem_open("/mySemaph", O_CREAT, S_IRUSR | S_IWUSR, 1); 
  //1 makes it a binary semaphore

  if(!sem){
    perror("something broke");
    exit(EXIT_FAILURE);
  }

  printf("%d: ready to wait\n", getpid()); 
  fflush(stdout);
  sem_wait(sem);

  printf("%d: obtained semaphore, working\n", getpid());
  fflush(stdout);
  sleep(5);
  sem_post(sem);

  printf("%d: release semaphore\n", getpid());
  fflush(stdout);

  sem_close(sem);

  exit(EXIT_SUCCESS);
}
