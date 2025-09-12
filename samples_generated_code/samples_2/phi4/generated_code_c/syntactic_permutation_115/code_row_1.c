#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    int result = system(command);
    if (result != 0) {
        printf("Command execution failed.\n");
    }
}

int main() {
    executeCommand("echo %s", "Hello, World!");
    
    return 0;
}