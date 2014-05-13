//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 5 | Part 2 uniqify

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <ctype.h>

#define WORDBUF_SIZE 1000

int main(int argc, char **argv){
  char *line = NULL;
  size_t len = 0;
  ssize_t readIn = 0;
  const char delimiters[] = " .,;:!-";
  char *running;
  char *token;

  while((readIn = getline(&line, &len, stdin)) != -1){
    running = strdupa(line);                /* Make writable copy.  */
    token = strsep (&running, delimiters);
    for(int i = 0; i<strlen(token)+1; i++){
      token[i] = tolower(token[i]);
    }
    printf("%s\n", token);
    while (token != NULL){
      token = strsep (&running, delimiters);
      if (token != NULL){
	for(int i = 0; i<strlen(token)+1; i++){
	  token[i] = tolower(token[i]);
	}
	printf("%s\n", token);
      }
    }
  }  
  exit(EXIT_SUCCESS);
}
