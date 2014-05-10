#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int aPipe[2];
  int bPipe[2];

  pipe(aPipe);
  pipe(bPipe);

  switch(fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    close(aPipe[0]);
    dup2(aPipe[1], STDOUT_FILENO);
    close(aPipe[1]);
    execlp("rev", "rev", (char *)0);
  default:
    break;
  }
  
  switch(fork()){
  case -1:
    perror("fork3");
    exit(EXIT_FAILURE);
  case 0:
    close(bPipe[0]);
    dup2(bPipe[1], STDOUT_FILENO);
    close(bPipe[1]);
    execlp("sort", "sort", (char *)0);
  default:
    break;
  }

  switch(fork()){
  case -1:
    perror("fork 4");
    exit(EXIT_FAILURE);
  case 0:
    close(bPipe[1]);
    dup2(bPipe[0], STDIN_FILENO);
    close(bPipe[1]);
    execlp("cat", "cat", (char *)0);
  default:
    break;
  }
  
  close(aPipe[0]);
  //  close(aPipe[1]);
  close(bPipe[0]);
  close(bPipe[1]);
  wait(NULL);
  wait(NULL);
  wait(NULL);
  //  wait(NULL);

  exit(EXIT_SUCCESS);
}
