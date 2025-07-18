#include <stdio.h>
    #include <stdlib.h>
    
    void ls(char *dir) {
        char command[1024];
        sprintf(command, "ls -l %s", dir);
        system(command);
    }
    
    int main() {
        char *dir = "/home/user";
        printf("Listing directory: %s\n", dir);
        ls(dir);
        return 0;
    }