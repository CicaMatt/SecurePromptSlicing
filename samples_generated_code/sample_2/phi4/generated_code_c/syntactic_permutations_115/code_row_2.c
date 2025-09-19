#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void printAndExecute(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int size = vsnprintf(NULL, 0, format, args) + 1; // Determine buffer length needed
    va_end(args);

    char *buffer = (char *)malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    executeCommand(buffer);
    free(buffer);
}

int main() {
    printAndExecute("ls -l %s", "some_directory_or_file");
    return 0;
}