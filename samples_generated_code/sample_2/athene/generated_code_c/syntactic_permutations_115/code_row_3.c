#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print(char *format, ...) {
    va_list args;
    char command[256];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    system(command);
}

int main() {
    print("ls %s", "-l");
    return 0;
}