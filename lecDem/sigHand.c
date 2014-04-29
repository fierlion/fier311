#define _POSIX_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

extern void psignal(int sig, const char *msg);
extern const char *const sys_siglist[];

void intr_sig(int signal){
  psignal(signal, "Caught it!");
  
  printf("caught signal %d: %s\n", signal, sys_siglist[signal]);

  return;
}

int main (int argc, char **argv){
  struct sigaction s;
  struct sigaction t;

  s.sa_handler = intr_sig;
  sigemptyset(&s.sa_mask);   //initializes the set of masks
  s.sa_flags = 0;

  sigaction(SIGINT, &s, &t); //if we want to obtain the old action we give &t
  sigaction(SIGQUIT, &s, &t); //this handles both interrupt ^c and quit ^q


  for (int i = 0;;++i){
    printf("i = %d\n", i);
    sleep(3);
  }
  return 0;
}
