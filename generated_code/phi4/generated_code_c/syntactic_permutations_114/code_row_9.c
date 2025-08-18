#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Using sprintf to create the command string with the ls utility
    sprintf(command, "ls");

    // Executing the command using system function
    int result = system(command);

    if (result == -1) {
        perror("system");
    }

    return 0;
}