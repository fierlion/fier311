#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int pfd[2];

  pipe(pfd);

  switch(fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    close(pfd[0]);
    dup2(pfd[1], STDOUT_FILENO);
    close(pfd[1]);
    execlp("cat", "cat", (char *)0);
    perror("cat fail exec");
    exit(EXIT_FAILURE);
  default:
    break;
  }

  switch(fork()){
  case -1:
    perror("fork2");
    exit(EXIT_FAILURE);
  case 0:
    close(pfd[1]);
    dup2(pfd[0], STDIN_FILENO);
    close(pfd[0]);
    execlp("cat", "cat", (char *)0);
    perror("wc fail exec");
    exit(EXIT_FAILURE);
  default:
    break;
  }

  close(pfd[0]);
  close(pfd[1]);
  wait(NULL);
  wait(NULL);

  exit(EXIT_SUCCESS);
}
