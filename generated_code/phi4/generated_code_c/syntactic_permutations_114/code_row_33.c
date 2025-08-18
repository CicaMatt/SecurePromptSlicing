#include <stdio.h>
#include <stdlib.h>

int main() {
    // Using sprintf to construct the command string
    char command[256];
    sprintf(command, "ls");

    // Execute the command using system function
    int result = system(command);

    // Check if the execution was successful
    if (result == -1) {
        printf("Failed to execute command\n");
    }

    return 0;
}