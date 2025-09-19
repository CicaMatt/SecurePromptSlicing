#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length of the formatted string
    int length = vsnprintf(NULL, 0, format, args);
    if (length < 0) return NULL;

    // Allocate memory for the formatted string
    char *buffer = malloc(length + 1);
    if (!buffer) return NULL;

    // Format the string into the allocated buffer
    va_start(args, format);
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}