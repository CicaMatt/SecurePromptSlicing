#include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>
    
    int main(void) {
      char *important_config;
      important_config = "Hello, world!";
      int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      write(fd, important_config, strlen(important_config));
    }