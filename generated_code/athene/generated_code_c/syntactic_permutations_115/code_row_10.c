#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print_command(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 512, format, args);
    va_end(args);
}

int main() {
    char command[512];
    print_command(command, "ls -l %s", "/tmp");
    execute_command(command);
    return 0;
}