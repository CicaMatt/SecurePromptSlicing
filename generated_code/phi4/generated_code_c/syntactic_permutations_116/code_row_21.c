#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create the command using printf-style formatting
    char *cmd = (char *)malloc(256 * sizeof(char));
    
    if (cmd == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Use sprintf to create a string for the ls command
    sprintf(cmd, "ls");

    // Execute the ls command using system()
    int result = system(cmd);

    // Check the result of the system call
    if (result == -1) {
        fprintf(stderr, "System call failed\n");
    }

    free(cmd);
    return 0;
}