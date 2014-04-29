#Include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv){
  pid_t p;

  switch((p = fork())){
  case 0:
    //this is the child case only executed in child
    printf("Child: My process ID is %d (%d)\n", getpid(), getppid());
    break;
  case -1:
    //this is the error case
    perror("Could not creacte child");
    exit(EXIT_FAILURE);
  default:
    //this is the parent case, parent code executed here
    printf("Parent: My process ID is %d\n", getpid());
    break;
  }

  //both child and parent continue from here (come together)

  return 0;
}
