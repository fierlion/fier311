//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Homework 3

//This program seeks various locations in a UNIX file
//usage: -f filename, -o offset, -l len, -O offset2, -e elen
//the program will open a file in the system, seek to the offset location
//read len number of bytes and write those to the console newline terminated.
//then it will seek the value -O relative to the current position in the file,
//read len (above) number of bytes and print those to the console newline
//terminated.  Finally it will print elen number of bytes from the end of 
//the file and write them to the console newline terminated.
//preconditions: values for len, offset, offset2, elen > 10000 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#define BLOCKSIZE 1


int main(int argc, char **argv){
  //getopt
  int c = 0;  
  extern char *optarg;
  extern int optind, optopt, opterr;
  //opt specific
  char *input;
  int offset1 = 0;
  int offset2 = 0;
  int len = 0;
  int elen = 0;
  //open()
  int fd;
  //read()
  char buf[BLOCKSIZE];
  int numRead;
  int numWrit;
  int count;
  //lseek()
  int newPos;

  //get command line args, any order, store in variables
  while ((c = getopt(argc, argv, ":f:o:l:O:e:")) != -1){
    switch(c){
    case 'f':
      input = optarg;
      break;
    case 'o':
      offset1 = atoi(optarg);
      break;
    case 'l':
      len = atoi(optarg);
      break;
    case 'O':
      offset2 = atoi(optarg);
      break;
    case 'e':
      elen = atoi(optarg);
      break;
    case ':':             // -folOe without operand
      printf("-%c needs an optarg\n", optopt);
      exit(EXIT_FAILURE);
    case '?':
      printf("unkown arg %c\n", optopt);
      exit(EXIT_FAILURE);
    }
  }

  //open input
  fd = open(input, O_RDONLY);
  if (fd == -1){
    perror("Can't open input file");
    exit(EXIT_FAILURE);
  }
  
  newPos = lseek(fd, offset1, SEEK_SET);
  
  printf("<offset 1>--------------------\n");
  while (((numRead = read(fd, buf, BLOCKSIZE)) > 0) && (count <= len)){ 
    numWrit = printf("%c", *buf);
    count +=1;

    if (numWrit != numRead){
      perror("Error reading file");
      exit(EXIT_FAILURE);
    }
  }
  printf("%c", '\n');



  exit(EXIT_SUCCESS);
}
