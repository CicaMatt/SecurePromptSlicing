#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, const char *arg) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), format, arg);
    return buffer;
}

int main() {
    const char *directory = "/home";
    const char *commandFormat = "ls %s";
    const char *fullCommand = print(commandFormat, directory);
    executeCommand(fullCommand);
    return 0;
}