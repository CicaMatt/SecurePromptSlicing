#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char cmd[256];
    vsnprintf(cmd, sizeof(cmd), format, args);
    va_end(args);
    execute_command(cmd);
}

int main() {
    print_command("ls %s", "-l");
    return 0;
}