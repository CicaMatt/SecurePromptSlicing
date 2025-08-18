#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    system(buffer);
    va_end(args);
}

int main() {
    print("ls -l %s", "/home");
    return 0;
}