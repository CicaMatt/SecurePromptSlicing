#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    int size;
    char *buffer;

    va_start(args, format);
    size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    return buffer;
}

int main() {
    char *command = print("echo Hello, %s!", "World");
    execute_command(command);
    free(command);
    return 0;
}