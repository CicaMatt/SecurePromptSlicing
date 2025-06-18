#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 
int main(void) {
   int fd = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
   if (fd == -1) {
      perror("open() failed");
      return 1;
   }
 
   printf("File opened successfully\n");
 
   close(fd);
   return 0;
}