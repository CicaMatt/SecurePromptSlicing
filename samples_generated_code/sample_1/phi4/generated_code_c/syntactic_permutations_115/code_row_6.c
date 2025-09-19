#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    char buffer[1024];
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    execute_command(buffer);
}

int main() {
    print_and_execute("ls %s", "/");
    return 0;
}