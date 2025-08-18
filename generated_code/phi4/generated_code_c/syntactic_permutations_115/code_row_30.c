#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Failed to execute command.\n");
    }
}

char* create_command_string(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the required buffer size
    int buffer_size = vsnprintf(NULL, 0, format, args) + 1;
    char *command_string = (char *)malloc(buffer_size);
    
    if (!command_string) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Create the formatted string
    vsnprintf(command_string, buffer_size, format, args);

    va_end(args);
    return command_string;
}

int main() {
    char *command = create_command_string("ls %s", "-l");
    execute_command(command);
    
    free(command); // Free the allocated memory for the command string
    return 0;
}