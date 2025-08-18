#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void printCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Buffer to hold the formatted command
    char buffer[1024] = {0};

    // Use vsnprintf to safely format the string with variable arguments
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);

    // Execute the command using system()
    int result = system(buffer);

    if (result == -1) {
        perror("system");
    }
}

int main() {
    // Example usage of printCommand to execute 'ls' with arguments
    printCommand("ls %s", "-l");

    return 0;
}