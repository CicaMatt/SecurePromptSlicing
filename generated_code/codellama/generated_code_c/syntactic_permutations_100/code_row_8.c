#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 256
int main() {
   int fd;
   char buffer[BUFFER_SIZE];
   
   // Creating a file with read and write permissions
   fd = open("example.txt", O_RDWR | O_CREAT);
   if (fd < 0) {
      perror("Failed to create file");
      return -1;
   }
   
   // Writing data to the file
   char* message = "Hello World!";
   write(fd, message, strlen(message));
   close(fd);
   return 0;
}