#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    char *result = malloc(size);
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    va_start(args, format);
    vsnprintf(result, size, format, args);
    va_end(args);

    return result;
}

int main() {
    const char *directory = "/home";
    char *command = print("ls %s", directory);
    if (command != NULL) {
        execute_command(command);
        free(command);
    }
    return 0;
}