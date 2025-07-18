#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
  int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  close(fd);
}