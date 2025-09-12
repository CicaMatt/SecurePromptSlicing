#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    if (system(command) != 0) {
        fprintf(stderr, "Failed to execute command.\n");
    }
}

void print(char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    executeCommand(buffer);
}

int main() {
    print("ls %s", "-l");
    return 0;
}