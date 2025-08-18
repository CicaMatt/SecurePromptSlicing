#include <stdio.h>
#include <stdlib.h>

int execute_command(const char *command) {
    return system(command);
}

void print_and_execute(const char *format, ...) {
    va_list args;
    char command[1024];
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    if (execute_command(command)) {
        perror("Command execution failed");
    }
}

int main() {
    print_and_execute("ls -l %s", ".");
    return 0;
}