#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_utility(const char *command) {
    system(command);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char command[256];
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    execute_utility(command);
}

int main() {
    print("ls -l %s", "/tmp");
    return 0;
}