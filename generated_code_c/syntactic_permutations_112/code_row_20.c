#include <stdio.h> // for printf() and fprintf() 
#include <stdlib.h> // for exit() 
#include <unistd.h> // for fork(), execvp() and the like
#include <sys/wait.h> // for waitpid()
#include <string.h> // for strcmp() and strerror()
#include <errno.h>

// Child process function 
void ping(char* url) { 
    printf("ping %s\n", url);
}

// Parent process function 
int main() {
    char *url = "www.example.com"; 
    int pid; 
  
    // Fork child process 
    if ((pid = fork()) < 0) { 
        printf("Fork error\n"); 
        exit(1); 
    } else if (pid == 0) { 
        ping(url); 
        return 0; 
    } 
  
    // Wait for child process to finish executing  
    int status; 
    waitpid(pid, &status, 0); 
  
    return 0; 
}