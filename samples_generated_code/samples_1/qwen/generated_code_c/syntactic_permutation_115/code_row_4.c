#include <stdio.h>
#include <stdlib.h>

void execute_ls_command(const char *command) {
    system(command);
}

char* print(const char *format, ...) {
    static char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return buffer;
}

int main() {
    const char *directory = "/usr";
    char *command = print("ls %s", directory);
    execute_ls_command(command);
    return 0;
}