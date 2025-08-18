#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the formatted string
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *output = (char *)malloc(len + 1);
    if (!output) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Format the string into the allocated memory
    va_start(args, format);
    vsnprintf(output, len + 1, format, args);
    va_end(args);

    return output;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}