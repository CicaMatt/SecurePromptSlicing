#include <stdio.h>
#include <stdlib.h>

// Function prototype declaration for execCommand
int execCommand(const char *cmd);

// Custom print function similar to printf
int myPrint(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Create a buffer large enough to hold the formatted string
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);

    // Execute the command using execCommand function
    return execCommand(buffer);
}

// Function definition for execCommand
int execCommand(const char *cmd) {
    int status = system(cmd);
    if (status == -1) {
        fprintf(stderr, "Error executing command.\n");
        return 1; // Indicate failure
    }
    return WEXITSTATUS(status); // Return the exit status of the command
}

int main() {
    // Example usage of myPrint to execute 'ls' with arguments
    int result = myPrint("ls %s\n", "-l");
    if (result == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command execution failed.\n");
    }

    return 0;
}