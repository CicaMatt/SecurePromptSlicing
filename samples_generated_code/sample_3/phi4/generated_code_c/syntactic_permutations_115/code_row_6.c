#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

char* create_format_string(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the length of the resulting string
    int size = 0;
    const char *p = format;
    while (*p != '\0') {
        if (*p == '%') p++;  // Skip '%' to find next character
        size += (*p == '\0') ? 1 : 2;  // +2 for "%d" or similar, +1 for literal characters
        p++;
    }
    
    va_end(args);

    char *result = (char *)malloc(size);
    if (!result) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    va_start(args, format);
    vsnprintf(result, size, format, args);
    va_end(args);

    return result;
}

int main() {
    char *command = create_format_string("ls -l %s", "/usr");
    execute_command(command);
    
    free(command);
    return 0;
}