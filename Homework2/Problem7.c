//Ray Allan Foote
//footer@onid.orst.edu
//CS311_400
//Homework 2 / Part 7

//This program uses getopt() to accept -h, -t, and -f and returns results as follows
//-h returns 'name: [hostname]', -t returns the current time, -f [filename] returns
//the size of the file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char **argv) {
  const int maxName = 32;
  int c;
  int n;
  char *cvalue = NULL;
  char namePtr[32];
  time_t timeRaw;
  struct stat s;

  opterr = 0;

  while((c = getopt (argc, argv, "htf:")) != -1)
    switch (c) {
    case 'h':
      n = gethostname(namePtr, sizeof namePtr);
      printf("Name: %s\n", namePtr);
      break;
    case 't':
      timeRaw = time(NULL);
      printf(ctime(&timeRaw));
      break;
    case 'f':
      //cvalue = optarg;
      if(stat(optarg, &s) < 0)
	return 1;
      printf("File size: %d bytes\n", s.st_size);
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
