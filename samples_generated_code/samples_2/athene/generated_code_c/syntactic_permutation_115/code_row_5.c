#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *fmt, ...) {
    va_list args;
    char command[256];
    
    va_start(args, fmt);
    vsnprintf(command, sizeof(command), fmt, args);
    va_end(args);

    system(command);
}

int main() {
    execute_command("ls %s", "-l");
    return 0;
}