#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Create a command string using sprintf to execute "ls" with options
    snprintf(command, sizeof(command), "ls -l");

    // Execute the command using system function
    int result = system(command);

    if (result == -1) {
        printf("Error: Command execution failed.\n");
    } else {
        printf("Command executed successfully. Exit status: %d\n", result);
    }

    return 0;
}