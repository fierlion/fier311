#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 10

int main(int argc, char **argv){
  int pfd[2];
  //char buf[BUF_SIZE];
  //ssize_t numRead;

  //  if (argc !=2 || strcmp(argv[1], "--help") == 0){
  //  perror("cant get args");
  //  exit(EXIT_FAILURE);
  //}

  if (pipe(pfd) == -1)
    perror("Can't make pipe");

  switch (fork()) {
  case -1:
    perror("Fork error");

  case 0:                                  //first child: exec ls to write pipe
    if (close(pfd[0]) == -1)               //read end is unused
      perror("close - lchild");
    //duplicate stdout on write end of pipe; close duplicated descriptor

    if (pfd[1] != STDOUT_FILENO){
      if (dup2(pfd[1], STDOUT_FILENO) == -1)
	perror("dup failed child 1");

      if (close(pfd[1]) == -1)
	perror("close parent child2");
    }

    execlp("ls", "ls", (char *) NULL);
    exit(EXIT_FAILURE);                 //execlp overlays the process image

  default:                              //parent writes to pipe
    break;
  }

  switch (fork()){
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:                               //second child: exec wc to read pipe
    if (close(pfd[1]) == -1)            //close write end
      perror("close parent");

    //duplicate stdin on read end of pipe; close duplicated descriptor

    if (pfd[0] != STDIN_FILENO) {
      if(dup2(pfd[0], STDIN_FILENO) == -1)
	perror("dup failed child2");

      if (close(pfd[0]) == -1)
	perror("close 4");

    }      
      execlp("wc", "wc", "-l", (char *)NULL);
      exit(EXIT_FAILURE);
  default:
    break;
  }

  //parent closes unused file descriptors and waits for children

  if(close(pfd[0]) == -1)
    perror("close 5");

  if(close(pfd[1]) == -1)
    perror("close 6");

  if(wait(NULL) == -1)
    perror("Wait 1");

  if(wait(NULL) == -1)
    perror("Wait 2");

  exit(EXIT_SUCCESS);
}
