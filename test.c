#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void) {
  char *filename = "data";
  int fd;
  fd = open(filename, O_WRONLY|O_APPEND|O_CREAT);

  // The STDOUT descriptor is redirected to refer to the 
  // same "thing" as the fd descriptor.
  dup2(fd, STDOUT_FILENO);
  write(fd,"Text 2", 5*sizeof(char));
  puts("Text 1");

  fsync(fd);
  close (fd);

  // When writing to stdout, data will now be written to the file.

}
