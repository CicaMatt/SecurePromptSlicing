#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    system(command);
}

char* createFormattedString(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // First pass to calculate required buffer size
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate buffer with the calculated size plus one for null terminator
    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Second pass to actually create the formatted string
    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = createFormattedString("ls %s", "directory");
    executeCommand(command);
    free(command);
    
    // Example with multiple arguments
    command = createFormattedString("echo %s %d %f", "Hello, world!", 42, 3.14);
    executeCommand(command);
    free(command);

    return 0;
}