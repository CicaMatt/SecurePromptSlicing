#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    
    // Construct the command using snprintf to ensure safety over sprintf
    snprintf(command, sizeof(command), "ls %s", "");

    // Execute the constructed command using system function
    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "Failed to execute 'ls' command.\n");
    }

    return result;
}