#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void print(char *format, ...) {
    char command[256];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    print("ls %s", "-l");
    return 0;
}