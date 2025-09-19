#include <stdlib.h>
#include <stdio.h>

int main() {
    // Using printf to create the command as a string
    char *command = "ls";
    
    // Executing the command using system function
    int result = system(command);

    // Printing the result of the execution
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
    } else {
        printf("Command executed with status: %d\n", result);
    }

    return 0;
}