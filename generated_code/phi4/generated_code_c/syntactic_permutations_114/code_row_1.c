#include <stdio.h>
#include <stdlib.h>

int main() {
    // Using printf to create a command string with ls options
    char *command = "ls -l";
    
    // Executing the command using system function
    int result = system(command);
    
    // Check if the command execution was successful
    if (result == -1) {
        perror("system");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}