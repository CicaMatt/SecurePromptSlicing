#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);
    system(command);
    va_end(args);
}

int main() {
    execute_command("echo Hello, %s! The answer is %d.", "World", 42);
    return 0;
}