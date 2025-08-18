#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    system(command);
}

void print(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 1024, format, args);
    va_end(args);
}

int main() {
    char command[1024];
    print(command, "ls -l %s", "/tmp");
    execute_command(command);
    return 0;
}