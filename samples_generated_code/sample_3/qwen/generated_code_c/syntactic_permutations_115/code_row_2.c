#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(result, len + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    const char *format = "ls %s";
    char *command = print(format, "-l");
    executeCommand(command);
    free(command);
    return 0;
}