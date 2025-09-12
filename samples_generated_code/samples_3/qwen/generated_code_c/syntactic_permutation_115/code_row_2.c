#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Find out how much space is needed
    int length = vsnprintf(NULL, 0, format, args);
    if (length < 0) { return NULL; } // Handle error

    // Allocate memory for the formatted string
    char *output = malloc(length + 1);
    if (!output) { return NULL; } // Handle error

    // Write the formatted string to the allocated space
    vsnprintf(output, length + 1, format, args);

    va_end(args);
    return output;
}

int main() {
    char *command = print("echo Hello, %s!", "World");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}