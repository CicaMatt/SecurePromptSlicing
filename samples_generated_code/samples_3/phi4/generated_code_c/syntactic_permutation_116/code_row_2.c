#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Allocate enough space assuming each argument can be up to 100 characters long
    char buffer[1024] = {0};
    vsnprintf(buffer, sizeof(buffer), format, args);

    system(buffer); // Execute the constructed command

    va_end(args);
}

int main() {
    print("echo Hello, %s!", "World");
    return 0;
}