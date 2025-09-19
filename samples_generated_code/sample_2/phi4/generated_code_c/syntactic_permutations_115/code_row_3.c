#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
}

char* create_command_string(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Estimate the maximum possible size
    int buffer_size = 1024; 
    char *buffer = malloc(buffer_size);
    if (!buffer) return NULL;

    while (1) {
        va_list copy;
        va_copy(copy, args);
        int required_size = vsnprintf(NULL, 0, format, copy) + 1;
        va_end(copy);

        if (required_size > buffer_size) {
            free(buffer);
            buffer_size = required_size;
            buffer = malloc(buffer_size);
            if (!buffer) return NULL;
        } else {
            vsnprintf(buffer, buffer_size, format, args);
            break;
        }
    }

    va_end(args);
    return buffer;
}

int main() {
    char *command_str = create_command_string("ls %s", "-l");
    if (command_str) {
        execute_command(command_str);
        free(command_str);
    } else {
        fprintf(stderr, "Failed to create command string\n");
    }
    
    return 0;
}