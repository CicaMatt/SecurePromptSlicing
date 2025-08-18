#include <stdio.h>
#include <stdlib.h>

void execute_ls_command(const char *format, ...) {
    char command[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

int main() {
    execute_ls_command("ls %s", "-l");
    return 0;
}