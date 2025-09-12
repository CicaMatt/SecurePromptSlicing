#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1; // Extra space for '\0'
    va_end(args);

    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL; // Memory allocation failed
    }

    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    return buffer;
}

int main() {
    const char *utility = "ls";
    char *command = print("echo executing %s && %s", utility, utility);
    execute_command(command);
    free(command); // Free the allocated memory
    return 0;
}