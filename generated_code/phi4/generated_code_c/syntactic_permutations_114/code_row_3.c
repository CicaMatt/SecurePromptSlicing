#include <stdio.h>
#include <stdlib.h>

int main() {
    // Using printf with a format string to create the command
    char command[20];
    snprintf(command, sizeof(command), "ls");

    // Execute the ls command using system function
    int result = system(command);

    // Check if the execution was successful
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
    }

    return 0;
}