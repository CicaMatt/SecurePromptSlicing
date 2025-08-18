#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("Failed to execute command");
    }
}

#define MAX_ARGS 100

void printAndExecute(const char *format, ...) {
    va_list args;
    char command[MAX_ARGS] = {0};
    
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);

    executeCommand(command);
}

int main() {
    printAndExecute("ls -l %s", "some_directory");
    return 0;
}