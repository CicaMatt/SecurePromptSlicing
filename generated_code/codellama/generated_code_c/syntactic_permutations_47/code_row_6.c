#include <stdio.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <unistd.h>
    
    void send_file(char *path) {
      //TODO
    }
    
    void handler() {
        char path[100] = {'\0'};
        strcat(path, "images/");
        struct stat buffer;   
        if(stat("images", &buffer) == 0){
          send_file(path);
        } else {
          printf("File does not exist.");
        }
      }