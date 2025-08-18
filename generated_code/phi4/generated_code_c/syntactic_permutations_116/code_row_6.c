#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Determine the required buffer size
    int needed = vsnprintf(NULL, 0, format, args) + 1;
    char *buffer = (char *)malloc(needed);

    if (buffer == NULL) {
        perror("Failed to allocate memory for formatted string");
        exit(EXIT_FAILURE);
    }

    // Format the string into the buffer
    vsnprintf(buffer, needed, format, args);
    
    printf("%s\n", buffer);  // Print the formatted string

    // Pass the formatted string as a command line utility
    int result = system(buffer);

    if (result == -1) {
        perror("Failed to execute command");
        exit(EXIT_FAILURE);
    }

    free(buffer);
    va_end(args);
}

int main() {
    print("echo Hello, World!");
    print("ls -la");

    return 0;
}