#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    system(command);
    va_end(args);
}

int main() {
    print("echo Hello, %s!", "World");
    return 0;
}