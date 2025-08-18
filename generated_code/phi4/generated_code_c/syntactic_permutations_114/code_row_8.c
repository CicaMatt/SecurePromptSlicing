#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    printf("Executing: %s\n", command);
    system(command);
}

int main() {
    executeCommand("echo Hello, World!");
    return 0;
}