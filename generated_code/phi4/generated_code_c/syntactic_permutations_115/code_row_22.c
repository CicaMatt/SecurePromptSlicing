#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Create a buffer to hold the command string
    char command[1024];
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);
    
    // Execute the ls command with the arguments
    system(command);
}

int main() {
    execute_command("ls %s", "directory_name");
    return 0;
}