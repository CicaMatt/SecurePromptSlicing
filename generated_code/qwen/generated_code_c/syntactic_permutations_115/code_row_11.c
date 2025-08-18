#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate length of resulting string
    int len = vsnprintf(NULL, 0, format, args);
    if (len == -1) return NULL;

    // Allocate memory for the string
    char *str = malloc(len + 1);
    if (!str) return NULL;

    // Write formatted string into allocated memory
    va_start(args, format); // Restart argument list processing
    vsnprintf(str, len + 1, format, args);

    va_end(args);
    return str;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        executeCommand(command);
        free(command);
    }
    return 0;
}