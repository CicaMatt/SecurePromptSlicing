#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the formatted string
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    // Allocate memory for the formatted string
    char *buffer = (char*)malloc((len + 1) * sizeof(char));
    if (!buffer) {
        return NULL;
    }

    // Format the string into the allocated buffer
    va_start(args, format);
    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = print("ls %s", "-l");
    if (command) {
        executeCommand(command);
        free(command);
    }
    return 0;
}