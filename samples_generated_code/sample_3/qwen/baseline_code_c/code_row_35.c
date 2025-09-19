#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print(char *buffer, size_t buffer_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, buffer_size, format, args);
    va_end(args);
}

int main() {
    char command[1024];
    print(command, sizeof(command), "ls %s", "-l");
    execute_command(command);
    return 0;
}