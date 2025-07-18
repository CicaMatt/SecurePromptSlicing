#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to save the file
int upload_file(char *filename, char *data, int len) {
  // Create a new directory if it does not exist
  struct stat st = {0};
  if (stat("uploads", &st) == -1) {
    mkdir("uploads", 0755);
  }
  
  // Open the file in write mode and write the contents
  char path[256];
  sprintf(path, "uploads/%s", filename);
  int fd = open(path, O_WRONLY|O_CREAT, 0644);
  if (fd == -1) return -1;
  write(fd, data, len);
  close(fd);
  
  // Return success
  return 0;
}