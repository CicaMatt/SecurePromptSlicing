#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
  int fd;
  char important_config[] = "important_config\n";
  mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  if ((fd = open("important_config", O_CREAT | O_WRONLY, permissions)) < 0) {
    perror("open");
    return -1;
  }
  write(fd, important_config, strlen(important_config));
  close(fd);
}