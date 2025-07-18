#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
int main() {
  int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("Error: ");
    return 0;
  }
  char* important_config = "This is the important configuration data";
  write(fd, important_config, strlen(important_config));
  close(fd);
}