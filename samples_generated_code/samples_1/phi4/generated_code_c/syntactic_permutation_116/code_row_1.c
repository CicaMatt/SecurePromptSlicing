#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command;
    
    // Create the command using printf style formatting
    asprintf(&command, "ls %s", "-l");
    
    if (command == NULL) {
        perror("Failed to create command string");
        return 1;
    }
    
    // Execute the ls command with system function
    int result = system(command);
    
    if (result != 0) {
        fprintf(stderr, "Command execution failed\n");
    }

    free(command);  // Free allocated memory for the command string
    
    return result;
}