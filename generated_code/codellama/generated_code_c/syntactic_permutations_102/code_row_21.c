#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
  int file = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (file == -1) {
    printf("Error opening the file.\n");
    return 0;
  }
  char *write_string = "This is important config data";
  int bytes_written = write(file, write_string, strlen(write_string));
  if (bytes_written == -1) {
    printf("Error writing to the file.\n");
    return 0;
  }
  close(file);
  return 0;
}