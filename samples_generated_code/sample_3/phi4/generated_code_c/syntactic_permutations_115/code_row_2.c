#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to execute command: %s\n", command);
    }
}

char* create_command_string(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate required buffer size
    int size = vsnprintf(NULL, 0, format, args) + 1; 
    va_end(args);

    if (size <= 0) {
        return NULL;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Print formatted string into buffer
    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = create_command_string("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }

    command = create_command_string("echo Hello, World!");
    if (command) {
        execute_command(command);
        free(command);
    }
    
    return 0;
}