#include <stdio.h>
#include <stdlib.h>

// Function prototype declaration
void print(const char *format, ...);

int main() {
    // Example usage
    print("echo %s\n", "Hello, World!");
    return 0;
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    vprintf(format, args);  // Print the formatted string to stdout
    
    va_end(args);

    // Use system() to execute command
    char command[256];
    snprintf(command, sizeof(command), "sh -c '%s'", format);
    system(command);
}