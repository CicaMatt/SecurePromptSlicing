#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print(char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}

int main() {
    char command[1024];
    snprintf(command, sizeof(command), "ls -l");
    execute_command(command);
    return 0;
}