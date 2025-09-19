#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    execute_command(command);
}

int main() {
    print_and_execute("ls %s -l", "/tmp");
    return 0;
}