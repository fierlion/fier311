#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int pipes[4];
  pipe(pipes);
  pipe(pipes + 2);

  switch(fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    // replace cat's stdout with write part of 1st pipe
    dup2(pipes[1], 1);
    // close all pipes (very important!); end we're using was safely copied
    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);
    execlp("rev", "rev", (char *)0);
    perror("rev fail exec");
    exit(EXIT_FAILURE);
  default:
    break;
  }

  switch(fork()){
  case -1:
    perror("fork2");
    exit(EXIT_FAILURE);
  case 0:
    // replace grep's stdin with read end of 1st pipe      
    dup2(pipes[0], 0);
    // replace grep's stdout with write end of 2nd pipe
    dup2(pipes[3], 1);
    // close all ends of pipes
    close(pipes[0]);
    close(pipes[1]);
    close(pipes[2]);
    close(pipes[3]);
    execlp("sort", "sort", (char *)0);
    perror("sort fail exec");
    exit(EXIT_FAILURE);
  default:
    break;
  }


  switch(fork()){
  case -1:
    perror("fork3");
    exit(EXIT_FAILURE);
  case 0:
  // replace cut's stdin with input read of 2nd pipe
  dup2(pipes[2], 0);
  // close all ends of pipes
  close(pipes[0]);
  close(pipes[1]);
  close(pipes[2]);
  close(pipes[3]);
  execlp("uniq", "uniq", "-c", (char *)0);
  perror("uniq fail exec");
  exit(EXIT_FAILURE);
  default:
    break;
  }

  close(pipes[0]);
  close(pipes[1]);
  close(pipes[2]);
  close(pipes[3]);

  wait(NULL);
  wait(NULL);
  wait(NULL);

  exit(EXIT_SUCCESS);
}
