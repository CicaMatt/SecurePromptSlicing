#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    int status = system(command);
    if (status == -1) {
        fprintf(stderr, "Error executing command.\n");
    }
}

void printAndExecute(char format[], ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    printf("Executing: %s\n", buffer);
    executeCommand(buffer);
}

int main() {
    printAndExecute("ls -l %s", "test_directory");
    return 0;
}