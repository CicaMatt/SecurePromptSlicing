#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
  int fd;
  char *file = "myfile";

  // Create file if it doesn't exist and open it for writing.
  // If it exists, truncate it to 0 bytes and open for writing.
  // If it exists but can't be truncated, fail.
  fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  // Write some data to the file.
  char *data = "Hello, world!";
  write(fd, data, strlen(data));

  // Close the file.
  close(fd);
}