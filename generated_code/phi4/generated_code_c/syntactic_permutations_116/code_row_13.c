#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Create the command string using printf
    sprintf(command, "ls %s", "-l");

    // Execute the ls command using system function
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
    }

    return 0;
}