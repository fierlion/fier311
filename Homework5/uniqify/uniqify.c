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

struct messy {
  long mtype;
  char mtext[30]; //longest english word < 30
  int count;
};

int main(int argc, char **argv){
  char *line = NULL;
  size_t len = 0;
  ssize_t readIn = 0;
  const char delimiters[] = " .,;:!-";
  char *running;
  char *token;
  int toklen;
  //msgqueue
  struct messy buf;
  int msqid;
  key_t key;

  if ((key = ftok("uniqify.c", 'B')) == -1){
    perror("ftok");
    exit(EXIT_FAILURE);
  }
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1){
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  buf.mtype = 1;

  while((readIn = getline(&line, &len, stdin)) != -1){
    running = strdupa(line);                /* Make writable copy.  */
    token = strsep (&running, delimiters);
    toklen = sizeof(token);
    for(int i = 0; i< toklen-1; i++){
      token[i] = tolower(token[i]);
    }
    if (strncmp(token, buf.mtext, toklen) == 0){
      buf.count += 1;
    }
    else {
      memcpy(buf.mtext, token, toklen);
      printf("%s\n", buf.mtext);
    }
    if (msgsnd(msqid, &buf, toklen, 0) == -1)
      perror("msgsend");
    while (token != NULL){
      token = strsep (&running, delimiters);
      
      if (token != NULL){    //bug here: if token previous is null, strlen wrong
	toklen = sizeof(token);
	for(int i = 0; i<toklen - 1; i++){
	  token[i] = tolower(token[i]);
	}
	if (strncmp(token, buf.mtext, toklen) == 0){
	  buf.count += 1;
	}
        else {
          memcpy(buf.mtext, token, toklen);
          printf("%s\n", buf.mtext);
	  if (msgsnd(msqid, &buf, toklen, 0) == -1)
	      perror("msgsend2");
	}
	  
	
	//      printf("%s\n", token);
      }
    }
    //if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    //  perror("msgctl");
    //  exit(EXIT_FAILURE);
    //}
  }  
  exit(EXIT_SUCCESS);
}
