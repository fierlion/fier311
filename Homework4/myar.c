//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 4 | Part 2

//This program illustrates the use of file I/O by managing a UNIX archive library
//in the standard archive format.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

#define BLOCKSIZE 1            //text files have a blocksize of 1


int main(int argc, char **argv){
  int c;
  char *input;
  char *output;
  
  int in_fd;
  int out_fd;

  char buf[BLOCKSIZE];

  int num_read;
  int num_written;

  while((c = getopt(argc, argv, "q:x:t:vd:A")) != -1){
    switch(c){
    case 'q':                  //append named files to .a, if no members create empty .a file
      if (optarg)
	//handle optarg
	printf("%s", optarg);
      else
	//create empty .a file
      break;
    case 'x':                  //extract (copy out) named members, if no arg, extract all
      if (optarg)
	//handle optarg
	printf("%s", optarg);
      else
	//extract all
      break;                   
    case 't':                  //print a concise table of .a contents
      break;
    case 'v':                  //print a verbose table
      break;
    case 'd':                  //delete named files from .a, if no arg nothing happens
      if (optarg)
	//handle optarg
	printf("%s", optarg);
      break;
    case 'A':                  //append all regular files in current dir, (except .a)
      break;
    case '?':
      if (isprint(optopt))
	fprintf(stderr, "Unknown option -%c\n", optopt);
      else
	fprintf(stderr, "Unknown option character %x\n", optopt);
      exit(EXIT_FAILURE);
    default:
      printf("Unable to get command opts...Exiting");
      exit(EXIT_FAILURE);
    }


  }
  return 0;
}
