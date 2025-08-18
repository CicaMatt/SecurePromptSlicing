#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the size needed for the formatted string
    int size = vsnprintf(NULL, 0, format, args) + 1;
    if (size <= 0) { return NULL; }

    // Allocate memory for the formatted string
    char *result = malloc(size);
    if (!result) { return NULL; }

    // Format the string into the allocated buffer
    vsnprintf(result, size, format, args);

    va_end(args);

    return result;
}

int main() {
    char *command = print("echo Hello, %s!", "World");
    executeCommand(command);
    free(command);
    return 0;
}