#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void) {
  int fd;
  char *important_config = "important_config";
  if ((fd = open("file.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
    return 0;
  }
  write(fd, important_config, strlen(important_config));
  close(fd);
  return 0;
}