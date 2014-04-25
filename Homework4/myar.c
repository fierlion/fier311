//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Assignment 4 | Part 2

//This program illustrates the use of file I/O by managing a UNIX archive library
//in the standard archive format.

#define _GNU_SOURCE
#define _BSD_SOURCE
#define _SVID_SOURCE

#include <ar.h>
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
#include <assert.h>

#define BLOCKSIZE 1            //text files have a blocksize of 1
#define NEWLINE "\n"

//http://www.johnloomis.org/ece537/notes/Files/Examples/ls2.html
void showFileInfo(char*, struct stat*);
void modeToLetters(int, char[]);
 
void printUse();
void openAdd(char* fileIn, char *fileOut);
char* makeHeader(char* fileIn, char* headIn);
struct ar_hdr* getStat(char* fileIn);
void printStat(char* fileIn);


int main(int argc, char **argv){
  int c;

  int getopt(int argc, char * const argv[], const char *opstring);
  extern char *optarg;
  extern int optind, opterr, optopt;
  
  char *input;
  char *output = argv[2];

  char *permsOut;
  
  struct ar_hdr* fileDeets = malloc(sizeof(struct ar_hdr));
  assert (fileDeets != 0);

  opterr = 0;                    //disable invalid options
  while ((c = getopt(argc, argv, "q:x:tvd:A")) != -1)
    switch(c){
    case 'q':                  //append named files to .a, if no members create empty .a file
      for ( ;optind < argc && *argv[optind] != '\0'; optind++){
	openAdd(argv[optind], output);
      }
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

void openAdd(char* fileIn, char* fileOut){
  char *input = fileIn;
  char *output = fileOut;
  char *header = malloc(70);
 
  int in_fd;
  int out_fd;
  off_t seekPos;

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
  write(out_fd, ARMAG, SARMAG);
  seekPos = lseek(out_fd, 0, SEEK_END);

  //if (seekPos % 2  == 0)
  //  write(out_fd, NEWLINE, 1);

  //get write permissions string
  header = makeHeader(fileIn, header);
  write(out_fd, header, 70);
  write(out_fd, ARFMAG, 2);   

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

char *makeHeader(char* filein, char* headIn){
  int headSize = 70;
  strcat(headIn, "This is a header");
  
  headIn[headSize - 1] = '\0';
  //printf("%s\n", headIn);
  return headIn;
  }
  
struct ar_hdr* getStat(char* fileIn){
  struct stat sb;
  struct ar_hdr* fileDeetsOut = malloc(sizeof(struct ar_hdr));
  assert (fileDeetsOut != 0);

  if (stat(fileIn, &sb) == -1){
    perror("stat");
    exit(EXIT_FAILURE);
  }
  else
    showFileInfo(fileIn, &sb);

  return fileDeetsOut;
}

void printStat(char* fileIn){
  struct stat sb;
  if (stat(fileIn, &sb) == -1){
    perror("stat");
    exit(EXIT_FAILURE);
  }
  else
    showFileInfo(fileIn, &sb);
}

void showFileInfo(char *filename, struct stat *info_p){
  char*uid_to_name(), *ctime(), *gid_to_name(), *filemode();
  void modeToLetters();
  char    modestr[11];

  modeToLetters( info_p->st_mode, modestr );

  printf( "%s"    , modestr);
  printf( "%4d "  , (int) info_p->st_nlink);
  printf( "%d/"   , (int) info_p->st_uid);
  printf( "%d "   , (int) info_p->st_gid);
  printf( "%8ld " , (long)info_p->st_size);
  printf( "%.12s ", 4+ctime(&info_p->st_mtime));
  printf( "%s\n"  , filename );
  return;
}

void modeToLetters( int mode, char str[] ){
  strcpy( str, "----------" );           /* default=no perms */

  if ( S_ISDIR(mode) )  str[0] = 'd';    /* directory?       */
  if ( S_ISCHR(mode) )  str[0] = 'c';    /* char devices     */
  if ( S_ISBLK(mode) )  str[0] = 'b';    /* block device     */

  if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
  if ( mode & S_IWUSR ) str[2] = 'w';
  if ( mode & S_IXUSR ) str[3] = 'x';

  if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
  if ( mode & S_IWGRP ) str[5] = 'w';
  if ( mode & S_IXGRP ) str[6] = 'x';

  if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
  if ( mode & S_IWOTH ) str[8] = 'w';
  if ( mode & S_IXOTH ) str[9] = 'x';
  return;
}
