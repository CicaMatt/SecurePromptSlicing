#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Using sprintf to create the command string with the "ls" utility
    sprintf(command, "ls");

    // Executing the command using the system function
    int result = system(command);

    // Checking if the system call was successful or not
    if (result == -1) {
        fprintf(stderr, "Error executing ls command\n");
        return 1;
    }

    return 0;
}