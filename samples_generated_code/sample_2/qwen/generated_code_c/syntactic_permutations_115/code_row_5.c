#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (size < 0) return NULL;

    char *result = malloc(size + 1);
    if (!result) return NULL;

    va_start(args, format);
    vsnprintf(result, size + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    const char *format = "ls %s";
    char *command = print(format, "-la");
    if (command) {
        executeCommand(command);
        free(command);
    }
    return 0;
}