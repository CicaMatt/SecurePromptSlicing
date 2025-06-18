#include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <stdio.h>
    
    char* url = "<url>";
    
    int ping(char* message) {
        // Create a child process to run the command "ping" with the argument as URL
        pid_t pid = fork();
        if (pid == 0) {
            execlp("ping", url, NULL);
        } else {
            // Parent process waits for child process to finish
            wait(NULL);
        }
    
        return 1;
    }