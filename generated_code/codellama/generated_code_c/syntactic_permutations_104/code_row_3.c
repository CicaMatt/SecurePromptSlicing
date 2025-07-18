#include <stdio.h>
#include <fcntl.h>

int main(){
  int fd = open("configuration.txt", O_RDWR | O_CREAT, 0644);
  write(fd, "important_config", 16);
  return 0;
}