#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void exec_ls(const char *format, ...) {
    va_list args;
    char command[256];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    system(command);
}

int main() {
    exec_ls("ls -l %s", "/tmp");
    return 0;
}