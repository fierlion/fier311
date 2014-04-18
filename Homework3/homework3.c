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

int main(int argc, char **argv){
  //getopt
  int c;  
  extern char *optarg;
  extern int optind, optopt, opterr;
  //opt specific
  char *ifile;
  int offset1, offset2;
  int len;
  int elen;
  //open()
  int ofile;
  //read()
  char buffer[10000]; 

  //get command line args, any order, store in variables
  while ((c = getopt(argc, argv, ":f:o:l:O:e:")) != -1){
    switch(c){
    case 'f':
      ifile = optarg;
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

  printf("-f: %s, -o: %i, -l: %i, -O: %i, -e: %i\n", ifile, offset1,
	 len, offset2, elen);

  //open ifile
  ofile = open(ifile, O_RDONLY);
  if (ofile < 0){
    printf("unable to open %s\n", ifile);
    exit(EXIT_FAILURE);
  }
  
  printf("file open: %i\n", ofile);

  //read ofile
  if (read(ofile, buffer, len) != len){
    printf("read %s for %i chars failed\n", ifile, len);
  }
  printf("%s\n", buffer);

  if (lseek(ofile, offset1, SEEK_SET) < 0){
    printf("lseek for %i offset1 failed\n", offset1);
  }
  if (read(ofile, buffer, len) != len) {
    printf("read %s for %i chars failed\n", ifile, len);
  }
  printf("%s\n", buffer);

  exit(EXIT_SUCCESS);
}
