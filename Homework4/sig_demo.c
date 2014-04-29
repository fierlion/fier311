//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 4 | Part 1

//This program sends and recieves Unix signals.  It installs 3 different 
//functions as signal handlers, handling SIGINT, SIGUSR1 & 2

#define _POSIX_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern void psignal(int sig, const char *msg);
extern const char *const sys_siglist[];

//signal handlers
void intrSig_q(int signal){ 
  printf("SIGUSR1 has been caught\n");
  return;
}
void intrSig_r(int signal){
  printf("SIGUSR2 has been caught\n");
  return;
}
void intrSig_s(int signal){
  printf("SIGINT has been caught, terminating the program\n");
  exit(EXIT_FAILURE);
}

int main (int argc, char **argv){
  struct sigaction q;
  struct sigaction r;
  struct sigaction s;
  struct sigaction t;

  q.sa_handler = intrSig_q;
  sigemptyset(&q.sa_mask);   //initializes the q set of masks
  q.sa_flags = 0;

  r.sa_handler = intrSig_r;
  sigemptyset(&r.sa_mask);   //initializes the r set of masks
  r.sa_flags = 0;

  s.sa_handler = intrSig_s;
  sigemptyset(&s.sa_mask);   //initializes the s set of masks
  s.sa_flags = 0;

  sigaction(SIGINT, &s, &t); //if we want to obtain the old action we give &t
  sigaction(SIGUSR1, &q, &t); //this handles both interrupt ^c and quit ^q
  sigaction(SIGUSR2, &r, &t); 

  //printf("sending SIGUSR1\n");
  kill(getpid(), SIGUSR1);
  //printf("sending SIGUSR2\n");
  kill(getpid(), SIGUSR2);
  //printf("sending SIGINT\n");
  kill(getpid(), SIGINT);

  //shouldn't ever reach here
  return 0;
}
