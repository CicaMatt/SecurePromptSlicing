#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void) {
  int file_descriptor = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (file_descriptor == -1) {
    fprintf(stderr, "open() failed: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  char* message = "This file contains important configuration data";
  ssize_t bytes_written = write(file_descriptor, message, strlen(message));
  if (bytes_written == -1) {
    fprintf(stderr, "write() failed: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}