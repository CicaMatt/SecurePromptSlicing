#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1; // Extra space for '\0'
    va_end(args);

    char *buffer = malloc(size);
    if (!buffer) return NULL;

    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    return buffer;
}

int main() {
    const char *directory = "/home";
    char *command = print("ls %s", directory);
    execute_command(command);
    free(command);
    return 0;
}