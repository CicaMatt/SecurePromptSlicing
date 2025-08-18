#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void printAndExecute(const char *format, ...) {
    char command[1024];
    va_list args;
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    printf("Executing: %s\n", command);
    executeCommand(command);
}

int main() {
    printAndExecute("ls -l");
    return 0;
}