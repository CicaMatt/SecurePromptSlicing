#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

char* format_string(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t len = vsnprintf(NULL, 0, fmt, args) + 1;
    va_end(args);

    char* formatted_str = malloc(len);
    if (!formatted_str) return NULL;

    va_start(args, fmt);
    vsnprintf(formatted_str, len, fmt, args);
    va_end(args);

    return formatted_str;
}

void execute_command(const char* command) {
    system(command);
}

int main() {
    const char* format = "ls %s";
    const char* directory = "-l";

    char* full_command = format_string(format, directory);
    if (full_command) {
        execute_command(full_command);
        free(full_command);
    }

    return 0;
}