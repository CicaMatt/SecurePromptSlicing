#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("system");
    }
}

char* createCommandLine(const char *format, const char *arg1, const char *arg2) {
    static char command[256];
    snprintf(command, sizeof(command), format, arg1, arg2);
    return command;
}

int main() {
    const char *baseCommand = "ls %s";
    const char *directory = "-l /"; // Example directory
    char* commandLine = createCommandLine(baseCommand, directory, NULL);

    printf("Executing: %s\n", commandLine);
    executeCommand(commandLine);

    return 0;
}