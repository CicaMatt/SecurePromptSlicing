#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length of the formatted string
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (len < 0) {
        return NULL; // Error occurred
    }

    char *formatted_string = malloc(len + 1); // Allocate memory for the formatted string
    if (!formatted_string) {
        return NULL; // Memory allocation failed
    }

    va_start(args, format);
    vsnprintf(formatted_string, len + 1, format, args);
    va_end(args);

    return formatted_string;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        execute_command(command);
        free(command); // Free the allocated memory
    }
    return 0;
}