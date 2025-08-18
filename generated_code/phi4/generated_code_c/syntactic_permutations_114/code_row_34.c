#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Create the ls command with desired options, e.g., "-l" to list in long format
    snprintf(command, sizeof(command), "ls -l");
    
    // Execute the command using system()
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
    }
    
    return 0;
}