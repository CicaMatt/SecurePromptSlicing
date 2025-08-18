#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *fmt, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, fmt);
    vsnprintf(command, sizeof(command) - 1, fmt, args);
    va_end(args);

    system(command);
}

int main() {
    execute_command("echo Hello, %s!", "World");
    return 0;
}