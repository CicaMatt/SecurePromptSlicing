#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    char *result = malloc(size);
    if (result == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(result, size, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    executeCommand(command);
    free(command);
    return 0;
}