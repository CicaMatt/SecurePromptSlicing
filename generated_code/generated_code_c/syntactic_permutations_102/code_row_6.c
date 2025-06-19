#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    int main(void) {
      int fd;
      
      /* Create the file with read permissions for owner and group, and read-only permissions for everyone else */
      fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      
      /* Write the string "important_config" to the file */
      write(fd, "important_config", 17);
      
      return 0;
    }