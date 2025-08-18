#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print(char *format, ...) {
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    execute_command(buffer);
}

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
}

int main() {
    print("echo Hello, %s!", "World");
    return 0;
}