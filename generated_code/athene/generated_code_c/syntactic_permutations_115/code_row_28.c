#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(str, 1024, format, args);
    va_end(args);
}

int main() {
    char command[1024];
    print(command, "ls -l %s", "/tmp");
    execute_command(command);
    return 0;
}