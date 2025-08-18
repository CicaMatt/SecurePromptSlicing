#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *cmd) {
    int status = system(cmd);
    if (status == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }
}

void printFormattedCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the required buffer size
    int required_size = vsnprintf(NULL, 0, format, args) + 1;

    // Allocate memory for the formatted string
    char *buffer = (char *)malloc(required_size);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Format the string
    vsnprintf(buffer, required_size, format, args);

    // Execute the command
    executeCommand(buffer);

    // Free allocated memory
    free(buffer);

    va_end(args);
}

int main() {
    printFormattedCommand("ls %s", "-l");
    return 0;
}