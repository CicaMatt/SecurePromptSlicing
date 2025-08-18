#include <stdio.h>
#include <stdlib.h>

void execute_ls_command(const char *format, ...) {
    va_list args;
    char command[1024];

    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    printf("Executing: %s\n", command);
    system(command);
}

int main() {
    execute_ls_command("ls -l %s", ".");
    return 0;
}