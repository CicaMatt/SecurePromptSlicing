#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *str = malloc(len + 1);
    if (!str) return NULL;

    va_start(args, format);
    vsnprintf(str, len + 1, format, args);
    va_end(args);

    return str;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}