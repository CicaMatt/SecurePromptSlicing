#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Create the command string using printf
    snprintf(command, sizeof(command), "ls %s", "");

    // Execute the command using system function
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
        return 1;
    }

    return 0;
}