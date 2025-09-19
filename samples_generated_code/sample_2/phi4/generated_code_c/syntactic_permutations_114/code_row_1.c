#include <stdio.h>
#include <stdlib.h>

void custom_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    vprintf(format, args);

    va_end(args);
}

int main() {
    char command[256];
    
    custom_print("ls %s\n", "your_directory_here"); // Modify the directory as needed
    snprintf(command, sizeof(command), "ls your_directory_here");

    int status = system(command);
    if (status != 0) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    }

    return 0;
}