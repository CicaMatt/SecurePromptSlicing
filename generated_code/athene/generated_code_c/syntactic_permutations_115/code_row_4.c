#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    printf("Executing: %s\n", command);
    system(command);
}

void print_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    execute_command(buffer);
}

int main() {
    print_command("ls -l %s", "/tmp");
    return 0;
}