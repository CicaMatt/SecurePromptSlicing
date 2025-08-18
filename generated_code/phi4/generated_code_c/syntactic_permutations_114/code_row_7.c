#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Allocate buffer for formatted string (arbitrarily chosen size)
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);

    printf("Executing: %s\n", command);
    system(command);
}

int main() {
    execute_command("echo Hello, World!");
    
    return 0;
}