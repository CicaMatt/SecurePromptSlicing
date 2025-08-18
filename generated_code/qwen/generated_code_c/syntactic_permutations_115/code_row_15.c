#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_ls_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");

    char command[1024];
    vsnprintf(command, sizeof(command), format, args);
    system(command);

    va_end(args);
}

int main() {
    execute_ls_command("ls %s", "-l");
    return 0;
}