#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];

    // Using sprintf to create the command string with ls parameters
    sprintf(command, "ls");

    // Execute the command using system function
    int result = system(command);

    if (result == -1) {
        printf("Error executing command\n");
    }

    return 0;
}