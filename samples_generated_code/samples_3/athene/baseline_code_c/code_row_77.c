#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print(char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    execute_command(buffer);
}

int main() {
    print("ls -l %s", "/tmp");
    return 0;
}