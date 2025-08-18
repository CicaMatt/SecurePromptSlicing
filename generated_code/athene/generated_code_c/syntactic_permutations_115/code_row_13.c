#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char cmd[1024];
    vsnprintf(cmd, sizeof(cmd), format, args);
    va_end(args);
    execute_command(cmd);
}

int main() {
    print("ls -l %s", "/tmp");
    return 0;
}