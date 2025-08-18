#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *output = malloc(size + 1);
    if (!output) return NULL;

    va_start(args, format);
    vsnprintf(output, size + 1, format, args);
    va_end(args);

    return output;
}

int main() {
    const char *format = "echo Hello, %s!";
    char *command = print(format, "World");
    if (command) {
        execute_command(command);
        free(command);
    }
    return 0;
}