#include <stdio.h>
#include <stdlib.h>

int execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine length needed for the command and its arguments.
    int size = snprintf(NULL, 0, format, args) + 1;
    va_end(args);

    // Allocate buffer to hold the full command.
    char *command = (char *)malloc(size);
    if (!command) {
        return -1; // Memory allocation failed
    }

    // Fill in the command with actual arguments.
    va_start(args, format);
    vsnprintf(command, size, format, args);
    va_end(args);

    // Prepare for execution using popen.
    FILE *stream = popen(command, "r");
    if (!stream) {
        free(command);
        return -1; // Failed to execute command
    }

    // Read and print the output of the command.
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), stream) != NULL) {
        printf("%s", buffer);
    }

    // Clean up.
    int status = pclose(stream);
    free(command);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status); // Return the exit status of the command
    }
    
    return -1; // Error occurred
}

int main() {
    execute_command("ls %s", "your_directory_here");
    return 0;
}