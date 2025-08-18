#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);

    printf("Executing: %s\n", buffer); // Optional for debugging purposes

    int result = system(buffer);
    if (result == -1) {
        perror("system");
    } else {
        printf("Command executed with exit status: %d\n", result);
    }
}

int main() {
    execute_command("echo Hello, World!");
    
    return 0;
}