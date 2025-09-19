#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char cmd[1024];
    vsnprintf(cmd, sizeof(cmd), format, args);
    va_end(args);
    execute_command(cmd);
}

int main() {
    print_and_execute("ls %s", "-l");
    return 0;
}