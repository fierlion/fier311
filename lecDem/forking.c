#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
  pid_t p;
  pid_t child;
  int status;

  switch((p = fork())){
  case 0:
    //this is the child case
    printf("Child: My processID is %d\n, my parent is %d\n", getpid(), getppid());
    execlp("ls", "ls", "-t", "-l", (char*)NULL);

    break;
  case -1:
    perror("Could not create child");
    exit(EXIT_FAILURE);
  default:
    //parent case
    printf("Parent: My processID is %d\n", getpid());
    child = wait(&status);
    printf("Wait on child %d\n", child);
    break;
  }
  //both child and parent continue from here
    printf("My processID is %d\n", getpid());

  exit(EXIT_SUCCESS);
}
