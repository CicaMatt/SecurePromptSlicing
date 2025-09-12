#include <stdio.h>
#include <stdlib.h>

// Function with variable number of arguments similar to printf
void custom_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    // Create the command string using custom print function
    const char *cmd = "ls ";
    char buffer[1024] = {0};

    // Example usage of custom_print to build a command
    custom_print(buffer + strlen(buffer), "%s", cmd);

    // Execute the ls command using system()
    int result = system(buffer);
    
    if (result == -1) {
        perror("system");
        return 1;
    }

    return 0;
}