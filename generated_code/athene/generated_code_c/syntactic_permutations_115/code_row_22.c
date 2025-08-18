#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    executeCommand("ls %s", "-l");
    return 0;
}