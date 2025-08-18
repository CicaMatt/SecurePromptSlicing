#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    
    // Constructing command using sprintf
    sprintf(command, "ls");

    // Execute the ls command
    system(command);

    return 0;
}