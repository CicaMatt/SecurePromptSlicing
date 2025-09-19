#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void execute_command(const char *cmd);
int print(char **out, const char *format, ...);

int main() {
    // Create command string using the print function
    char *cmd;
    print(&cmd, "ls -l %s", "/");

    // Execute the ls command
    execute_command(cmd);

    // Free allocated memory for the command string
    free(cmd);
    
    return 0;
}

void execute_command(const char *cmd) {
    int status = system(cmd);
    if (status != 0) {
        fprintf(stderr, "Command execution failed with status %d\n", status);
    }
}

int print(char **out, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the size of the buffer needed
    int size = vsnprintf(NULL, 0, format, args) + 1; 

    // Allocate memory for the formatted string
    *out = malloc(size);
    if (*out == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        va_end(args);
        return -1;
    }

    // Format the string and store it in allocated memory
    vsnprintf(*out, size, format, args);

    va_end(args);
    return 0;
}