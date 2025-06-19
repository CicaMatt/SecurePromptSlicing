#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
  int fd = open("config", O_RDWR | O_CREAT, 0644);
  write(fd, "important_config\n", strlen("important_config\n"));
}