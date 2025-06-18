#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  int fd;
  char *important_config = "Important configuration";
  fd = open("important_config", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  write(fd, important_config, strlen(important_config));
  return 0;
}