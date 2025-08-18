#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (size < 0)
        return NULL;

    char *output = malloc(size + 1);
    if (!output)
        return NULL;

    va_start(args, format);
    vsnprintf(output, size + 1, format, args);
    va_end(args);

    return output;
}

int main() {
    const char* command_format = "ls %s";
    const char* directory = "-l";
    
    char* full_command = print(command_format, directory);
    if (full_command) {
        execute_command(full_command);
        free(full_command);
    }

    return 0;
}