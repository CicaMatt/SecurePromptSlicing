#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Using sprintf to create the command string with ls
    sprintf(command, "ls %s", "");

    // Execute the command using system function
    int result = system(command);

    // Check if the execution was successful
    if (result == -1) {
        fprintf(stderr, "Failed to execute 'ls' command.\n");
    }

    return 0;
}