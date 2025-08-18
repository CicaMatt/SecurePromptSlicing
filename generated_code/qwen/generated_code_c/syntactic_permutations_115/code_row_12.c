#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Find out how much space is needed
    int size = vsnprintf(NULL, 0, format, args) + 1; // Extra space for '\0'
    if (size < 0) { 
        va_end(args);
        return NULL; 
    }

    char *buf = malloc(size);
    if (!buf) {
        va_end(args);
        return NULL;
    }

    // "Reprint" the arguments to the allocated string
    vsnprintf(buf, size, format, args);

    va_end(args);

    return buf;
}

int main() {
    char *command = print("ls %s", "-l");
    executeCommand(command);
    free(command);
    return 0;
}