//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 4 | Part 2

//This program illustrates the use of file I/O by managing a UNIX archive library
//in the standard archive format.

#define _GNU_SOURCE
#define _BSD_SOURCE
#define _SVID_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

#define BLOCKSIZE 1            //text files have a blocksize of 1

int main(int argc, char **argv){
  int c;

  int getopt(int argc, char * const argv[], const char *opstring);
  extern char *optarg;
  extern int optind, opterr, optopt;
  char *input;
  char *output = argv[1];

  void printUse();
  void openAdd(char* fileIn, char *fileOut);
  void printStat(char* fileIn);
  
  opterr = 0;                    //diable invalid options
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
	printStat(output);
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

 void openAdd(char *fileIn, char *fileOut){
   char *input = fileIn;
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
  
void printStat(char* fileIn){
  struct stat sb;

  if (stat(fileIn, &sb) == -1){
    perror("stat");
    exit(EXIT_FAILURE);
  }

  printf("protection %o\n", sb.st_mode);   
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

    printf("I-node number:            %ld\n", (long) sb.st_ino);

    printf("Mode:                     %lo (octal)\n",
	   (unsigned long) sb.st_mode);

    printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
	   (long) sb.st_uid, (long) sb.st_gid);

    printf("Preferred I/O block size: %ld bytes\n",
	   (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
	   (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
	   (long long) sb.st_blocks);

    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

  return;
}
