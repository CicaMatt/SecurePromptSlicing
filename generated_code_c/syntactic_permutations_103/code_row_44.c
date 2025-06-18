#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(void) {
   int fd;
   if ((fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
      perror("open");
      return 1;
   }
   // do stuff with fd here
   close(fd);
   return 0;
}