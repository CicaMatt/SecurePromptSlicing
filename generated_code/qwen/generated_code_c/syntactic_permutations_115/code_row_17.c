#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void exec_ls_command(const char *command) {
    system(command);
}

void custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    const char *ls_command = "ls -l";
    exec_ls_command(ls_command);

    custom_printf("This is a formatted string with a number: %d and a string: %s\n", 42, "example");

    return 0;
}