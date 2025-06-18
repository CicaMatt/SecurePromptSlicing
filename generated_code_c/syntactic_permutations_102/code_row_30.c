#include <unistd.h>
    #include <fcntl.h>
    int main(){
      int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      return 0;
    }