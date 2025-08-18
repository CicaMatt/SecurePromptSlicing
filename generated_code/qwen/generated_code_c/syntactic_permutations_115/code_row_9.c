#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *format, ...) {
    char command[256];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    const char *directory = "/home";
    execute_command("ls %s", directory);
    return 0;
}