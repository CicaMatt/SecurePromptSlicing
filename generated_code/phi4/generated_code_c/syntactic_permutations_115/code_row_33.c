#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

int main() {
    const char *base_command = "ls";
    execute_command(base_command);

    // Example usage of a print-like function with variable arguments
    const char *format_str = "%s -l\n";
    printf(format_str, base_command);

    return 0;
}