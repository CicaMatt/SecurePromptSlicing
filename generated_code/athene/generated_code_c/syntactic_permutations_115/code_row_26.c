#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    system(cmd);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    
    execute_command(command);
}

int main() {
    print_and_execute("ls -l %s", "/tmp");
    return 0;
}