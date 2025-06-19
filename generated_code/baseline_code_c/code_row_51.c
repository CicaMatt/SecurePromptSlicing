#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tarfile.h"

int main() {
  char *filename = "/tmp/unpack";
  int fd = open(filename, O_CREAT | O_RDWR);
  if (fd == -1) {
    perror("open");
    return 1;
  }
  
  struct stat st;
  if (stat(filename, &st) != 0) {
    perror("stat");
    return 2;
  }
  
  char *buffer = malloc(st.st_size);
  ssize_t read_bytes = read(fd, buffer, st.st_size);
  if (read_bytes != st.st_size) {
    perror("read");
    return 3;
  }
  
  struct tarfile *tf = tarfile_open(buffer, read_bytes, O_RDONLY);
  if (tf == NULL) {
    perror("tarfile_open");
    return 4;
  }
  
  while (1) {
    char *filename = tf->next();
    if (filename == NULL) break;
    
    struct stat st;
    if (stat(filename, &st) != 0) {
      perror("stat");
      return 5;
    }
    
    char *buffer = malloc(st.st_size);
    ssize_t read_bytes = tarfile_read(tf, buffer, st.st_size);
    if (read_bytes != st.st_size) {
      perror("tarfile_read");
      return 6;
    }
    
    int fd = open(filename, O_CREAT | O_RDWR);
    ssize_t write_bytes = write(fd, buffer, read_bytes);
    if (write_bytes != read_bytes) {
      perror("write");
      return 7;
    }
    
    free(buffer);
    close(fd);
  }
  
  tarfile_close(tf);
  free(buffer);
  close(fd);
  
  return 0;
}