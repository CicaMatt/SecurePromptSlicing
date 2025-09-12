#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    int status = system(command);
    if (status == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }
}

void printAndExecuteCommand(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Calculate the required buffer size
    int requiredSize = vsnprintf(NULL, 0, format, args) + 1;

    char *commandBuffer = (char *)malloc(requiredSize);
    if (!commandBuffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    vsnprintf(commandBuffer, requiredSize, format, args);

    // Execute the command
    executeCommand(commandBuffer);

    free(commandBuffer);
    va_end(args);
}

int main() {
    printAndExecuteCommand("ls %s", "/");

    return 0;
}