#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    va_end(args);
}

int main() {
    char command[256];
    print(command, "ls -la %s", "/path/to/directory");
    execute_command(command);
    return 0;
}