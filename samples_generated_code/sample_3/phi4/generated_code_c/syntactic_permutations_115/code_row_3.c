#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
    }
}

char* printFormat(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length of the final string
    size_t size = vsnprintf(NULL, 0, format, args) + 1; // +1 for null terminator
    va_end(args);

    // Allocate memory for the formatted string
    char *buffer = malloc(size);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Format the string with provided arguments
    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = printFormat("ls %s", "directory_name"); // Replace 'directory_name' as needed
    executeCommand(command);
    free(command);  // Free allocated memory

    return 0;
}