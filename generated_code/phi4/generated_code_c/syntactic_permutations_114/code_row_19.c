#include <stdio.h>
#include <stdlib.h>

// Function to execute ls command with variable arguments
void exec_ls(const char *format, ...) {
    char cmd[1024];
    va_list args;
    
    // Initialize the argument list
    va_start(args, format);
    
    // Create the formatted string for the command
    vsnprintf(cmd, sizeof(cmd), format, args);
    
    // End using the argument list
    va_end(args);

    // Execute the command
    system(cmd);
}

int main() {
    // Example usage: Listing files in the current directory with long listing format
    exec_ls("ls -l %s", ".");
    
    return 0;
}