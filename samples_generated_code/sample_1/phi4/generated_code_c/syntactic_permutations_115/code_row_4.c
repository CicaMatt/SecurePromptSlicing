#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    if (system(cmd)) {
        perror("Execution failed");
    }
}

void print_and_execute(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate buffer size
    int required_size = vsnprintf(NULL, 0, format, args) + 1; 
    char *cmd_buffer = (char *)malloc(required_size);
    
    if (cmd_buffer) {
        vsnprintf(cmd_buffer, required_size, format, args);
        execute_command(cmd_buffer);
        free(cmd_buffer);
    }

    va_end(args);
}

int main() {
    print_and_execute("ls %s", " -l");
    return 0;
}