#include <stdio.h>
#include <stdlib.h>
#define EXIT_FAILURE 1

void execute_cmd(const char *format, ...);

int main() {
    const char *command;
    command = "ls";
    execute_cmd(" %s", command);
}

void execute_cmd(const char *format, ...) {
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsprintf(buffer, format, args);
    system(buffer);
    va_end(args);
}