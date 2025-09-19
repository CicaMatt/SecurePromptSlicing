#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *cmd) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "sh -c '%s'", cmd);
    int result = system(buffer);
    if (result == -1) {
        perror("system");
    }
}

void print_and_execute(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a buffer large enough for typical commands
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);
    
    va_end(args);

    execute_command(command);
}

int main() {
    print_and_execute("ls -l %s", "/");

    return 0;
}