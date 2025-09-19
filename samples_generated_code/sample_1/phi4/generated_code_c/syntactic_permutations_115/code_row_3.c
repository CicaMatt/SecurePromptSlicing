#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void execute_command(const char *command) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "sh -c '%s'", command);
    int status = system(buffer);
    if (status != 0) {
        fprintf(stderr, "Command execution failed with status %d\n", status);
    }
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Calculate required buffer size
    int needed_size = vsnprintf(NULL, 0, format, args) + 1;
    char *buffer = malloc(needed_size);
    if (buffer != NULL) {
        vsnprintf(buffer, needed_size, format, args);

        execute_command(buffer);

        free(buffer);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    
    va_end(args);
}

int main() {
    print("ls -l %s", "/");  // Example usage
    return 0;
}