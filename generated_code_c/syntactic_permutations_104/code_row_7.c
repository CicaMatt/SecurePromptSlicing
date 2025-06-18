#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
int main(void) {
  int fd = open("/path/to/important_file", O_CREAT | O_WRONLY);
  if (fd == -1) {
    // Error handling
    return -1;
  }
  write(fd, "important_config", strlen("important_config"));
}