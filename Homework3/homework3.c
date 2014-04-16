//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Homework 3

//This program opens a file -f, seeks to the offset location -o, reads length -l 
//bytes from the file and writes those to the console, then seeks to -O offset2 
//relative to the current position, then again reads length -l bytes from the file
//and writes those bytes to the console.  It then read -e elen bytes from the 
//end of the file and prints them to the console.  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

#define BLOCKSIZE 1;

int main(int argc, char **argv) {
  int c;
  int n;
  char *cvalue = NULL;
  char namePtr[32];
  char *input;
  char *output;
  int inFd = 0;
  int outFd;
  char buf [1];

  int numRead;
  int numWritten;
  int copied;
  int fileSize;

  opterr = 0;

  while((c = getopt (argc, argv, "f:o:l:O:e:")) != -1)
    switch (c) {
    case 'f':
      inFd = open(optarg, O_RDONLY);
      if (inFd == -1){
	perror("can't open input file");
	exit(EXIT_FAILURE);
      }
      if (read(inFd, buf, 1) != 1){
	perror("Can't read file");
	exit(EXIT_FAILURE);
      }
      printf("%s\n", buf);
      break;
    case 'o':
      break;
    case 'l':
      //cvalue = optarg;                                                                    
      //if(stat(optarg, &s) < 0)
      //return 1;
      //printf("File size: %d bytes\n", s.st_size);
      break;
    case '?':
      if (optopt == 'c')
	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
	fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
      return 1;
    default:
      abort ();
  }
  return 0;
}

      /*
return 0;
}
  in_fd = open(input, O_RDONLY);
  if (in_fd == -1) {
    perror("Can't open input file");
    exit(-1);
  }

  out_fd = open(output, O_CREAT | O_WRONLY, 0777);
  if (out_fd == -1) {
    perror("Can't open/create file");
    exit(-1);
  }

  file_size = lseek(in_fd, -1, SEEK_END) + 1;     //need +1 because lseek is a byte shy

  while (copied < file_size) {
    num_read = read(in_fd, buf, BLOCKSIZE);
    num_written = write(out_fd, buf, BLOCKSIZE);

    if (num_written != num_read) {
      perror("error writing file");
      unlink(output);
      exit(-1);
    }

    copied += num_written;
    
    lseek(in_fd, -2, SEEK_CUR);  //one step forward two steps back--read moved forward
  }
      */
