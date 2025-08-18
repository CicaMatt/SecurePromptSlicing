#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *result = (char*)malloc(len + 1);
    if (!result) return NULL;

    va_start(args, format);
    vsnprintf(result, len + 1, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = print("ls %s", "-l");
    execute_command(command);
    free(command);
    return 0;
}