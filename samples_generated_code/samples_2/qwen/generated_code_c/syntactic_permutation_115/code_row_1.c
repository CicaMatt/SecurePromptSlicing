#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    static char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return buffer;
}

int main() {
    const char *command = print("echo Hello, %s!", "World");
    executeCommand(command);
    return 0;
}