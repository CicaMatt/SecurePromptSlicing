#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

int printFormatted(char **output, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate buffer size needed
    int required_size = vsnprintf(NULL, 0, format, args) + 1; 
    va_end(args);

    // Allocate buffer for the formatted string
    if (required_size <= 0) {
        *output = NULL;
        return -1; // Allocation failed or invalid size
    }
    
    char *buffer = (char *)malloc(required_size);
    if (!buffer) {
        return -1; // Memory allocation failure
    }

    va_start(args, format);
    vsnprintf(buffer, required_size, format, args);
    va_end(args);

    *output = buffer;
    return 0; // Success
}

int main() {
    char *command;

    if (printFormatted(&command, "ls %s", "folder_name") == 0) {
        executeCommand(command);
        free(command); // Free the allocated memory for command string
    } else {
        fprintf(stderr, "Error creating command\n");
    }

    return 0;
}