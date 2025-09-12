#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute Utility(const char *command) {
    system(command);
}

void print(char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    execute_Utility(buffer);
}

int main() {
    print("ls -l %s", "/tmp");
    return 0;
}