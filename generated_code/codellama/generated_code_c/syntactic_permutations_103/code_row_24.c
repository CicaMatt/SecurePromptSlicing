#include <fcntl.h>
#include <stdio.h>

int main(void) {
  int fd = open("myfile", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("open");
  } else {
    printf("File created successfully\n");
  }

  return 0;
}