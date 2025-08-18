#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *output = (char *)malloc((length + 1) * sizeof(char));
    if (!output) return NULL;

    va_start(args, format);
    vsnprintf(output, length + 1, format, args);
    va_end(args);

    return output;
}

int main() {
    const char *directory = "/home";
    char *command = print("ls %s", directory);
    executeCommand(command);
    free(command);
    return 0;
}