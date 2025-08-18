#include <stdio.h>
#include <stdlib.h>

// Function declaration
void execute_command(const char *command);
int print_and_execute(const char *format, ...);

int main() {
    // Example usage: Print and execute the command 'ls -l'
    if (print_and_execute("ls %s", "-l") != 0) {
        fprintf(stderr, "Failed to execute command\n");
    }
    return 0;
}

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("system failed");
        exit(EXIT_FAILURE);
    }
}

int print_and_execute(const char *format, ...) {
    char buffer[1024];
    va_list args;
    
    // Initialize the variable argument list
    va_start(args, format);

    // Print formatted string to a buffer
    int length = vsnprintf(buffer, sizeof(buffer), format, args);
    if (length < 0 || length >= sizeof(buffer)) {
        fprintf(stderr, "Buffer overflow\n");
        va_end(args);
        return -1;
    }
    
    // End the variable argument list processing
    va_end(args);

    // Execute the command
    execute_command(buffer);

    return 0;
}