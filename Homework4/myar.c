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
#include <string.h>
#include <getopt.h>

#define BLOCKSIZE 1            //text files have a blocksize of 1


int main(int argc, char **argv){
  int c;

  int getopt(int argc, char * const argv[], const char *opstring);
  extern char *optarg;
  extern int optind, opterr, optopt;         //disable invalid options
  char *input;
  char *output = "out.a";

  void printUse();
  void openAdd(char* fileOpenAdd, char *fileOut);
  
  opterr = 0;
  while ((c = getopt(argc, argv, "q:x:tvd:A")) != -1)
    switch(c){
      case 'q':                  //append named files to .a, if no members create empty .a file
        input = optarg;
	openAdd(input, output);
        break;
      case 'x':                  //extract (copy out) named members, if no arg, extract all
	printf("-x: %s\n", optarg);
        break;                   
      case 't':                  //print a concise table of .a contents
        printf("t\n");      
        break;
      case 'v':                  //print a verbose table
        printf("v\n");
        break;
      case 'd':                  //delete named files from .a, if no arg nothing happens 
        printf("-d: %s\n", optarg);
        break;
      case 'A':                  //append all regular files in current dir, (except .a)
        printf("A\n");
        break;
      case '?':
        if(optopt == 'q'){
	  printf("-q no arg\n");
	  //create empty file
	}  
	else if (optopt == 'x'){
	  printf("-x no arg\n");
	  //extract all
	}
	else if (optopt == 'd')
	  break;
	else
	  fprintf(stderr, "Unknown option -%c\n", optopt);
        break;
      default:
        printUse();
        exit(EXIT_FAILURE);
    }

  return 0;
}

void printUse(){
  printf("Useage: myar -q[file.a][files] | -x [file.a][files]\n");
  printf("        | -tv [file.a] | -d [file.a][files]\n");
  printf("        | -A [file.a]\n");
  return;
}

 void openAdd(char *fileOpenAdd, char *fileOut){
   char *input = fileOpenAdd;
   char *output = fileOut;
   
   int in_fd;
   int out_fd;

   char buf[BLOCKSIZE];
   
   int num_read;
   int num_written;

  in_fd = open(input, O_RDONLY);
  if (in_fd == -1){
    perror("Can't open input file");
    exit(EXIT_FAILURE);
  }
  
  out_fd = open(output, O_CREAT | O_WRONLY, 0666);
  if (out_fd == -1){
    perror("Can't open/create output file");
    exit(EXIT_FAILURE);
  }
  
  while((num_read = read(in_fd, buf, BLOCKSIZE)) > 0){
    num_written = write(out_fd, buf, BLOCKSIZE);

    if (num_written != num_read){
      perror("error writing file");
      unlink(output);
      exit(EXIT_FAILURE);
    }
  }
  return;
}
  
