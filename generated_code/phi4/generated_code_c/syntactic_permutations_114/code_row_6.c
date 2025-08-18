#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Create a buffer to hold the formatted string
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Execute the command using system function
    system(buffer);

    va_end(args);
}

int main() {
    print("echo Hello, World!");
    return 0;
}