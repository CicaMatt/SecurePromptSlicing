#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void print(char *buffer, size_t bufferSize, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, bufferSize, format, args);
    va_end(args);
}

int main() {
    char command[256];
    print(command, sizeof(command), "ls %s", "-l");
    executeCommand(command);
    return 0;
}