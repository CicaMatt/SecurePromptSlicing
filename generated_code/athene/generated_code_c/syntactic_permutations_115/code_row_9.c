#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void exec_ls(const char *args) {
    char command[256];
    snprintf(command, sizeof(command), "ls %s", args ? args : "");
    system(command);
}

int main() {
    print("Executing ls with arguments: ");
    print("%s\n", "-l");
    exec_ls("-l");
    return 0;
}