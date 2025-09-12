#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

void print_and_execute(char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine buffer size needed.
    int length = vsnprintf(NULL, 0, format, args) + 1; 
    char *buffer = (char *)malloc(length * sizeof(char));
    
    if (buffer != NULL) {
        vsnprintf(buffer, length, format, args);
        execute_command(buffer);
        
        free(buffer);
    }

    va_end(args);
}

int main() {
    print_and_execute("ls %s", "test_directory");
    return 0;
}