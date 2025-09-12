#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* command) {
    system(command);
}

void print(char* buffer, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
}

int main() {
    char command[1024];
    print(command, "ls %s", "-l");
    executeCommand(command);
    return 0;
}