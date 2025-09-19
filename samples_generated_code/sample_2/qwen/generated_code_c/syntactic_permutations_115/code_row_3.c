#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print(char *buffer, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, size, format, args);
    va_end(args);
}

void execute_command(const char *command) {
    system(command);
}

int main() {
    char command[256];
    print(command, sizeof(command), "ls %s", "-l");
    execute_command(command);
    return 0;
}