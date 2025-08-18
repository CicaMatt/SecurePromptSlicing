#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length of the formatted string
    int size = vsnprintf(NULL, 0, format, args) + 1; 
    if (size <= 0) { 
        va_end(args);
        return NULL;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        va_end(args);
        return NULL;
    }
    
    vsnprintf(buffer, size, format, args);

    va_end(args);
    return buffer;
}

int main() {
    const char *commandStr = print("ls %s", "-l");
    if (commandStr != NULL) {
        executeCommand(commandStr);
        free((void*)commandStr);  // Free the allocated memory for command string
    }
    
    return 0;
}