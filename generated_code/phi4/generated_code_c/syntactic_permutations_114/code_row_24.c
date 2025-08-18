#include <stdio.h>
#include <stdlib.h>

int main() {
    // Use printf with format specifiers to build the command
    char command[256];
    snprintf(command, sizeof(command), "ls %s", "");  // Add additional flags or directories as needed

    // Execute the 'ls' command using system()
    int result = system(command);

    // Check for errors in executing the command
    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}