#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_ls_command(const char *format, ...) {
    char command[256];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    execute_ls_command("ls %s", "-l");
    return 0;
}