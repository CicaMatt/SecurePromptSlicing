#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int executeCommand(char *command);
    
    int main() {
        char command[1024];
        sprintf(command, "ls %s", "-l");
        return executeCommand(command);
    }
    
    int executeCommand(char *command) {
        FILE *fp;
        char path[1035];
    
        fp = popen(command, "r");
        if (fp == NULL) {
            printf("Failed to run command\n" );
            return -1;
        }
    
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            printf("%s", path);
        }
    }