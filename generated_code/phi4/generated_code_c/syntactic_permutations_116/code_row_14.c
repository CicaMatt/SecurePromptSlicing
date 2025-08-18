#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Using snprintf to safely create the "ls" command string
    snprintf(command, sizeof(command), "ls");
    
    // Execute the system call with the ls command
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Error executing 'ls' command\n");
        return 1;
    }
    
    return 0;
}