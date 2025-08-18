#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
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
    const char *command_format = "ls %s";
    char *full_command = print(command_format, "-l");

    if (full_command != NULL) {
        execute_command(full_command);
        free(full_command);
    }

    return 0;
}