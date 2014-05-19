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

#define BLOCKSIZE 1
#define HEADSIZE 60

void printUse();
void openAdd(char* fileIn, char *fileOut);
void makeHeader(char* fileIn, char* headerIn);
void extract(char* arFile, char* fileIn);
struct ar_hdr* getStat(char* fileIn, struct ar_hdr* deetsIn);
void printName(char *fileIn);
//void showFileInfo(char*, struct stat*);
void modeToLetters(int, char[]);
void printStat(char* fileIn);


int main(int argc, char **argv){
  int c;
  int getopt(int argc, char * const argv[], const char *opstring);
  extern char *optarg;
  extern int optind, opterr, optopt;
  char *output = argv[2];
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
      for ( ;optind < argc && *argv[optind] != '\0'; optind++){
        extract(output, argv[optind]);
      }
      break;                   
    case 't':                  //print a concise table of .a contents
      printName(argv[2]);      
      break;
    case 'v':                  //print a verbose table
      printStat(argv[2]);
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
    }
  exit(EXIT_SUCCESS);
}

void printUse(){
  printf("Useage: myar -q[file.a][files] | -x [file.a][files]\n");
  printf("        | -tv [file.a] | -d [file.a][files]\n");
  printf("        | -A [file.a]\n");
  exit(EXIT_FAILURE);
}

void openAdd(char* fileIn, char* fileOut){
  char *input = fileIn;
  char *output = fileOut;
  char *header = malloc(HEADSIZE);
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
  makeHeader(fileIn, header);
  write(out_fd, header, strlen(header));
  seekPos = lseek(out_fd, 0, SEEK_END);
  write(out_fd, ARFMAG, 2);
  int oddCount = 0;
  while((num_read = read(in_fd, buf, BLOCKSIZE)) > 0){
    oddCount++;
    num_written = write(out_fd, buf, BLOCKSIZE);

    if (num_written != num_read){
      perror("error writing file");
      unlink(output);
      exit(EXIT_FAILURE);
    }
  }
  if (oddCount % 2 != 0)
    write(out_fd, "\n", sizeof(char));
  oddCount = 0;
  return;
}

void makeHeader(char* fileIn, char* headerIn){
  int nameSize = sizeof(fileIn);
  struct ar_hdr* deets = malloc(sizeof(struct ar_hdr));
  assert(deets != 0);
  getStat(fileIn, deets);
  int fileSize = strlen(deets->ar_size);
  strcat(headerIn, fileIn);
  strcat(headerIn, "/");
  while (sizeof(deets->ar_name) > nameSize){
    strcat(headerIn, " ");
    nameSize++;
  }
  strcat(headerIn, deets->ar_date);
  strcat(headerIn, "  ");
  strcat(headerIn, deets->ar_uid);
  strcat(headerIn, "   ");
  strcat(headerIn, deets->ar_gid);
  strcat(headerIn, "   ");
  strcat(headerIn, deets->ar_mode);
  strcat(headerIn, "  "); 
  strcat(headerIn, deets->ar_size);
  while (sizeof(deets->ar_size) > fileSize){
    strcat(headerIn, " ");
    fileSize++;
  }
}

struct ar_hdr* getStat(char* fileIn, struct ar_hdr* deetsIn){
  struct stat sb;

  if (stat(fileIn, &sb) == -1){
    perror("statGet");
    exit(EXIT_FAILURE);
  }
  sprintf(deetsIn->ar_name, "%s", fileIn);
  sprintf(deetsIn->ar_date, "%i", (int)(sb.st_mtime));
  sprintf(deetsIn->ar_uid, "%i", sb.st_uid);
  sprintf(deetsIn->ar_gid, "%i", sb.st_gid);
  sprintf(deetsIn->ar_mode, "%o", sb.st_mode);
  sprintf(deetsIn->ar_size, "%u", (unsigned)(sb.st_size));
  return deetsIn;
}

void extract(char* arFile, char* fileIn){
  char *input = arFile;
  int in_fd;
  int out_fd;
  off_t seekPos = 0;
  off_t seekEnd = 0;
  char fileName[16];
  char fileSize[10];
  char filePerm[4];
  int fileSizeInt = 0;
  char buf[BLOCKSIZE];
  int num_written = 0;

  in_fd = open(input, O_RDONLY);
  if (in_fd == -1){
    perror("Can't open input file");
    exit(EXIT_FAILURE);
  }
  seekEnd = lseek(in_fd, -1, SEEK_END);
  //find first filename
  seekPos = lseek(in_fd, 8, SEEK_SET);
  if(read(in_fd, fileName, sizeof(fileName)) != sizeof(fileName))
    exit(EXIT_FAILURE);
  while (seekPos < seekEnd) {
    if (strncmp(fileName, fileIn, strlen(fileIn)) == 0){
      seekPos = lseek(in_fd, seekPos + 42, SEEK_SET);
      read(in_fd, filePerm, strlen(filePerm));
      seekPos = lseek(in_fd, seekPos + 6, SEEK_SET);
      read(in_fd, fileSize, strlen(fileSize));
      out_fd = open(fileIn, O_CREAT | O_WRONLY, strtol(filePerm, NULL, 8));
      if(out_fd == -1){
	perror("Can't open -x output file");
	exit(EXIT_FAILURE);
      }
      seekPos = lseek(in_fd, seekPos + 12, SEEK_SET);
      while(num_written < atoi(fileSize)){
     	read(in_fd, buf, BLOCKSIZE); 
	write(out_fd, buf, BLOCKSIZE);
	num_written++;
      } 
      exit(EXIT_SUCCESS);
    }
    else seekPos = lseek(in_fd, seekPos + 48, SEEK_SET);
    if(read(in_fd, fileSize, sizeof(fileSize)) != sizeof(fileSize))
      exit(EXIT_FAILURE);
    fileSizeInt = atoi(fileSize); 
    if (fileSizeInt % 2 != 0){
      fileSizeInt++;
    }
    //find next 
    seekPos = lseek(in_fd, seekPos + fileSizeInt + 12, SEEK_SET);
    //get filename
    if(read(in_fd, fileName, sizeof(fileName)) != sizeof(fileName))
      break;
  }
  exit(EXIT_SUCCESS);
}

void printName(char *fileIn){
  char *input = fileIn;
  int in_fd;
  off_t seekPos = 0;
  off_t seekEnd = 0;
  char fileName[16];
  char fileSize[10];
  int fileSizeInt = 0;
  int i = 0;
  in_fd = open(input, O_RDONLY);
  if (in_fd == -1){
    perror("Can't open input file");
    exit(EXIT_FAILURE);
  }
  seekEnd = lseek(in_fd, -1, SEEK_END);
  //find first filename
  seekPos = lseek(in_fd, 8, SEEK_SET);
  if(read(in_fd, fileName, sizeof(fileName)) != sizeof(fileName))
    exit(EXIT_FAILURE);
  i = 0;
  while (i < 16){
    if(fileName[i] == '/')
      break;
    printf("%c", fileName[i]);
    i++;
  }
  printf("%c", '\n');   
  while (seekPos < seekEnd) {
    //get filesize
    seekPos = lseek(in_fd, seekPos + 48 , SEEK_SET);
    if(read(in_fd, fileSize, sizeof(fileSize)) != sizeof(fileSize))
      exit(EXIT_FAILURE);
    fileSizeInt = atoi(fileSize); 
    if (fileSizeInt % 2 != 0){
      fileSizeInt++;
    }
    //find next 
    seekPos = lseek(in_fd, seekPos + fileSizeInt + 12, SEEK_SET);
    //get filename
    if(read(in_fd, fileName, sizeof(fileName)) != sizeof(fileName))
      break;
    //print filename
    i = 0;
    while (i < 16){
      if(fileName[i] == '/')
        break;
      printf("%c", fileName[i]);
      i++;
      }
    printf("%c", '\n');
  }
exit(EXIT_SUCCESS);
}

void printStat(char* fileIn){
  struct ar_hdr* deets = malloc(sizeof(struct ar_hdr));
  void modeToLetters();  
  char *input = fileIn;
  int in_fd;
  off_t seekPos = 0;
  off_t seekEnd = 0;
  int fileSizeInt = 0;

  in_fd = open(input, O_RDONLY);
  if (in_fd == -1){
    perror("Can't open input file");
    exit(EXIT_FAILURE);
  }
  seekEnd = lseek(in_fd, -1, SEEK_END);
  //find first filename
  seekPos = lseek(in_fd, 8, SEEK_SET);
  while (seekPos < seekEnd) {
    //ar_name[16]
    read(in_fd, deets->ar_name, sizeof(deets->ar_name));
    seekPos = lseek(in_fd, seekPos + 16, SEEK_SET);
    //ar_date[12]
    read(in_fd, deets->ar_date, sizeof(deets->ar_date));
    seekPos = lseek(in_fd, seekPos + 12, SEEK_SET);
    //ar_uid[6]
    read(in_fd, deets->ar_uid, sizeof(deets->ar_uid));
    seekPos = lseek(in_fd, seekPos + 6, SEEK_SET);
    //ar_gid[6]
    read(in_fd, deets->ar_gid, sizeof(deets->ar_gid));
    seekPos = lseek(in_fd, seekPos + 6, SEEK_SET);
    //ar_mode[8]
    read(in_fd, deets->ar_mode, sizeof(deets->ar_mode));
    seekPos = lseek(in_fd, seekPos + 8, SEEK_SET);
    //ar_size[10]
    read(in_fd, deets->ar_size, sizeof(deets->ar_size));
    seekPos = lseek(in_fd, seekPos + 10, SEEK_SET);
    //ar_fmag[2]
    fileSizeInt = atoi(deets->ar_size);
    if (fileSizeInt % 2 != 0)
      fileSizeInt++;
    seekPos = lseek(in_fd, seekPos + fileSizeInt + 2, SEEK_SET);
    printf("%s\n", deets->ar_name);
  }
  exit(EXIT_SUCCESS);
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
