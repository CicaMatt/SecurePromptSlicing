#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the resulting string
    int len = vsnprintf(NULL, 0, format, args);
    if (len < 0) {
        va_end(args);
        return NULL; // Error occurred
    }

    // Allocate memory for the formatted string
    char *result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) {
        va_end(args);
        return NULL; // Memory allocation failed
    }

    // Format the string into the allocated buffer
    vsnprintf(result, len + 1, format, args);

    va_end(args);
    return result;
}

int main() {
    const char *command_format = "ls %s";
    char *command = print(command_format, "-l");

    if (command) {
        execute_command(command);
        free(command); // Don't forget to free the allocated memory
    }

    return 0;
}