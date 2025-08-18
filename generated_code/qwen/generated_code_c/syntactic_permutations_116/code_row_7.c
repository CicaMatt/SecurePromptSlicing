#include <stdio.h>
#include <stdlib.h>

void print(char *format, ...) {
    va_list args;
    char buffer[256];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    system(buffer);
}

int main() {
    print("echo Hello, %s!", "World");
    return 0;
}