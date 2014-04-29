#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCKSIZE 1

int main(int argc, char **argv)
{
  char *input = argv[1];
  char *output = argv[2];

  int in_fd;
  int out_fd;

  char buf[BLOCKSIZE];        //reversing block by block (aka byte by byte)

  int num_read;
  int num_written;
  int copied;

  int file_size;

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


  return 0;
}
