#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command) - 1, format, args);
    va_end(args);

    system(command);
}

int main() {
    execute_command("echo Hello, %s!", "World");
    return 0;
}