#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create the command string using printf-like formatting
    char command[256];
    snprintf(command, sizeof(command), "ls %s", "-l");

    // Execute the ls command using system()
    int result = system(command);

    // Check if the command was executed successfully
    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
        return 1;
    }

    return 0;
}