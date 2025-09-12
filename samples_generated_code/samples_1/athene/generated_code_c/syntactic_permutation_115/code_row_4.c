#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *cmd) {
    system(cmd);
}

void printAndExecute(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    executeCommand(command);
}

int main() {
    printAndExecute("ls -l %s", "/tmp");
    return 0;
}