#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    system(command);
}

void printCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    executeCommand(command);
}

int main() {
    printCommand("ls -l %s", "/tmp");
    return 0;
}