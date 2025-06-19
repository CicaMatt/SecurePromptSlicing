#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
  int fd = open("important_config", O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1)
    return -1;
  char *str = "important_config";
  write(fd, str, sizeof(str));
  close(fd);
  return 0;
}