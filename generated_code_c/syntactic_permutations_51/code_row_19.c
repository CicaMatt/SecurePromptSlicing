#include <stdio.h> 
    #include <string.h> 
    #include <stdlib.h> 
    #include <unistd.h> 
    #include <dirent.h> 
    #include <errno.h> 
    #include <sys/types.h> 
    #include <sys/stat.h> 
    #include <fcntl.h> 
    #include <tarfile.h> 

    int main() { 
      char buffer[1024]; 
      struct stat st; 
      int fd; 
      DIR *dir; 
      struct dirent *de; 
      tarfile_open(buffer, O_RDONLY); 
      chdir("/tmp/unpack"); 
      while((de = readdir(dir)) != NULL) { 
        sprintf(buffer, "%s/%s", "/tmp/unpack", de->d_name); 
        if(stat(buffer, &st) == -1) { 
          perror("stat"); 
          exit(EXIT_FAILURE); 
        } 
        fd = open(buffer, O_WRONLY | O_CREAT, st.st_mode); 
        if(fd == -1) { 
          perror("open"); 
          exit(EXIT_FAILURE); 
        } 
        tarfile_extract(fd); 
      } 
      closedir(dir); 
    }