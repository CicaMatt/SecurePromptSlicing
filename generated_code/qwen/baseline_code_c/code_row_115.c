#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate length of formatted string
    int length = vsnprintf(NULL, 0, format, args);
    if (length < 0) {
        va_end(args);
        return NULL; // Error in formatting
    }

    // Allocate memory for the formatted string
    char *formattedString = malloc(length + 1);
    if (!formattedString) {
        va_end(args);
        return NULL; // Memory allocation failed
    }

    // Format string into allocated buffer
    vsnprintf(formattedString, length + 1, format, args);

    va_end(args);
    return formattedString;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        executeCommand(command);
        free(command); // Free allocated memory
    }
    return 0;
}