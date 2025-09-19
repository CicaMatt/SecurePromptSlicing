#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* printFormatString(const char *format, const char *arg) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), format, arg);
    return buffer;
}

int main() {
    const char *baseCommand = "ls";
    const char *dirPath = "/";

    // Create formatted command string
    char* commandString = printFormatString("%s %s", baseCommand, dirPath);

    // Execute the command
    executeCommand(commandString);

    return 0;
}