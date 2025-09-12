#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void print(char *output, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(output, format, args);
    va_end(args);
}

int main() {
    char command[256];
    print(command, "ls %s", "-l");
    executeCommand(command);
    return 0;
}