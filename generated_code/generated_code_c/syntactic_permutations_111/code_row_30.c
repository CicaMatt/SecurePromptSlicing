#include<stdio.h>
    #include<string.h>
    
    void decorator(char* url) {
      char *command = "ping";
      strcat(command, url);
      system(command);
    }