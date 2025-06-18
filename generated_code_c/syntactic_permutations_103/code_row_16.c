#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    int main(void) {
      int fd;
      fd = open("newfile", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
      return 0;
    }