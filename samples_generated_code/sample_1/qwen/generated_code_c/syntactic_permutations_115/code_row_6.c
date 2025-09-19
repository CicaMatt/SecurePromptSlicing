#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // First pass: determine the length of the formatted string
    int length = vsnprintf(NULL, 0, format, args);
    if (length < 0) {
        va_end(args);
        return NULL;
    }

    // Allocate memory for the formatted string
    char *output = malloc(length + 1);
    if (!output) {
        va_end(args);
        return NULL;
    }

    // Second pass: fill the allocated buffer with the formatted string
    vsnprintf(output, length + 1, format, args);

    va_end(args);
    return output;
}

int main() {
    const char *directory = "/usr";
    char *command = print("ls %s", directory);
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}