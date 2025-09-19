#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Estimate size of buffer needed
    int size = vsnprintf(NULL, 0, format, args);
    if (size < 0) { return NULL; } // Error occurred

    char *buffer = malloc(size + 1); // Allocate memory for the formatted string
    if (!buffer) { return NULL; } // Memory allocation failed

    va_start(args, format); // Rewind arguments list
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        executeCommand(command);
        free(command);
    }
    return 0;
}