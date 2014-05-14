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
#include <search.h>

struct messy {
  long mtype;
  char mtext[30]; //longest english word < 30
  int count;
};

struct messy * makeMess(long type, char *mess, int count);
void freeMess(void *mess);
int messComp(const void *l, const void*r);
void walkTree(const void *mtext, VISIT x, int level);

int main(int argc, char **argv){
  char *line = NULL;
  size_t len = 0;
  ssize_t readIn = 0;
  int numChilds;
  int numWordsIn = 0;
  const char delimiters[] = " \"[]{}.,;:!-/*()?!@#$%^&_=+1234567890\\<>";
  char *running;
  char *token;
  int toklen;
  //msgqueue
  struct messy buf;
  int msqid;
  key_t key;
  //search
  //  static void *root = NULL;

  if ((key = ftok("uniqify.c", 'B')) == -1){
    perror("ftok");
    exit(EXIT_FAILURE);
  }
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1){
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  buf.mtype = 1;

  if(strcmp(argv[1], "-n") == 0){
    numChilds = atoi(argv[2]);
  }
  else numChilds = 1;

  //tokenize and put into mesQue
  while((readIn = getline(&line, &len, stdin)) != -1){
    running = strdupa(line);                /* Make writable copy.  */
    token = strsep (&running, delimiters);
    if (strcmp(token, "\n")){      
      toklen = strlen(token)+1;
      /* ditch newline at end, if it exists */
      if (token[toklen-2] == '\n') token[toklen-2] = '\0';    
      for(int i = 0; i< toklen-1; i++){
	token[i] = tolower(token[i]);
      }
      if (toklen > 1){
	memcpy(buf.mtext, token, toklen);
	buf.count = 1;
	numWordsIn += 1;
	//       	printf("%s, %d\n", buf.mtext, buf.count);
	if (msgsnd(msqid, &buf, toklen, 0) == -1)
	  perror("msgsend");    
      }
    }
    while(token != NULL){
      token = strsep (&running, delimiters);      
      if ((token != NULL) && (strcmp(token, "\n") != 0)){
	toklen = strlen(token)+1;
	/* ditch newline at end, if it exists */
	if (token[toklen-2] == '\n') token[toklen-2] = '\0';    
	for(int i = 0; i<toklen - 1; i++){
	  token[i] = tolower(token[i]);
	}
	if (toklen > 1){
	  memcpy(buf.mtext, token, toklen);
	  buf.count = 1;
	  numWordsIn += 1;
	  //printf("%s, %d\n", buf.mtext, buf.count);
	  if (msgsnd(msqid, &buf, toklen, 0) == -1)
	    perror("msgsend2");
	}
      }
    }
  }
   
  //make 3 children
  for (int j = 0; j < numChilds; j++){
    if (fork() == 0){
      void *tree = 0;
      struct messy *mt = 0;
      struct messy *retval = 0;
      for (int ja = 0; ja < (numWordsIn / numChilds); ja++){ 
	msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0);
	mt = makeMess(buf.mtype, buf.mtext, buf.count);
	//	printf("original %s\n", mt->mtext);
	retval = tsearch(mt, &tree, messComp);
	if(retval == 0){
	  printf("retval fail\n");
	}
	else{
	  struct messy *re = 0;
	  re = *(struct messy **)retval;
	  if(re != mt){
	    //printf("found existing ok %u\n", j);
	    re->count += 1;
	    //  printf("count = %d\n", mt->count);
	  }
	  else{
	    //printf("insert ok %u\n", j);
	  }
	}
      }
      twalk(tree, walkTree);
      exit(EXIT_SUCCESS);
    }
  }

  for (int k = 0; k < numChilds; k++){
    wait(NULL);
  }

  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }

  exit(EXIT_SUCCESS);
}

struct messy * makeMess(long type, char *mess, int count){
  struct messy *temp = (struct messy *)calloc(sizeof(struct messy),1);
  if (!temp){
    printf("calloc fail\n");
    exit(EXIT_FAILURE);
  }
  temp->mtype = type;
  strcpy(temp->mtext, mess);
  temp->count = count;
  return temp;
}


int messComp(const void *l, const void*r){
  const struct messy *ml = l;
  const struct messy *mr = r;
  if(strcmp(ml->mtext, mr->mtext) > 0)
    return 1;
  if(strcmp(ml->mtext, mr->mtext) < 0)
    return -1;
  return 0;
}

void walkTree(const void *mtext, VISIT x, int level){
  struct messy *m = *(struct messy **)mtext;
  if(x == postorder || x == leaf){
    printf("%s %d\n", m->mtext, m->count);
  } 
  return;
}
