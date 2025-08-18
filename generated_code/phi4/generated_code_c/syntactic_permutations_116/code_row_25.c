#include <stdio.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    const char *command = "ls";
    char buffer[256];

    // Using a variable argument list to create the command string
    print("Executing: %s\n", command);
    snprintf(buffer, sizeof(buffer), "%s", command);

    int result = system(buffer);
    
    if (result == -1) {
        perror("system");
    } else {
        printf("Command executed with exit status %d\n", result);
    }

    return 0;
}