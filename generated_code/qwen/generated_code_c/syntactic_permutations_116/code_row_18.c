#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    char command[50];
    print("Executing 'ls' command...\n");
    snprintf(command, sizeof(command), "ls");
    system(command);
    return 0;
}