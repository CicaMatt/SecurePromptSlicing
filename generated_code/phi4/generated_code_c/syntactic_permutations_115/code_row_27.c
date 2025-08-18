#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void printAndExecute(const char *format, ...) {
    va_list args;
    char buffer[1024];
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printf("Executing: %s\n", buffer);
    executeCommand(buffer);
}

int main() {
    printAndExecute("ls -l %s", ".");
    return 0;
}