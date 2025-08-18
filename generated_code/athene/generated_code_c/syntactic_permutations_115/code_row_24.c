#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    execute_command("ls -l %s", "/tmp");
    return 0;
}