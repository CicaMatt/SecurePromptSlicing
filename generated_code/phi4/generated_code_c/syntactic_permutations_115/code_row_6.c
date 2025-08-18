#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Command execution failed with status %d\n", result);
    }
}

int main() {
    execute_command("echo Hello, World!");
    return 0;
}