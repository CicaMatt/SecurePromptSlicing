#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Estimate the size of the buffer needed
    int size = vsnprintf(NULL, 0, format, args) + 1;
    if (size < 0) { 
        va_end(args);
        return NULL; 
    }

    char *buffer = malloc(size);
    if (!buffer) {
        va_end(args);
        return NULL;
    }

    // Format the string into the buffer
    vsnprintf(buffer, size, format, args);

    va_end(args);
    return buffer;
}

int main() {
    const char *format = "ls %s";
    char *command = print(format, "-l");

    if (command) {
        execute_command(command);
        free(command);
    }

    return 0;
}