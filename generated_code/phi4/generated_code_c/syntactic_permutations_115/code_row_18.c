#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void execute_command(const char *command) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "sh -c %s", command);
    int status = system(buffer);
    if (status != 0) {
        fprintf(stderr, "Command execution failed with status: %d\n", status);
    }
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), format, args);

    execute_command(buffer);

    va_end(args);
}

int main() {
    print("ls -l");  // Example usage
    return 0;
}