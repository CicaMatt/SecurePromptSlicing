#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
// ...
int main(void) {
  char important_config[256] = "some important configuration data";
  int fd = open("important_data", O_RDWR | O_CREAT);
  if (fd == -1) {
    // Handle error
  }
  write(fd, important_config, strlen(important_config));
  close(fd);
}