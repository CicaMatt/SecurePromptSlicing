#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute Utility(const char *cmd) {
    system(cmd);
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    executeUtility(buffer);
}

int main() {
    print("ls -l %s", "/tmp");
    return 0;
}