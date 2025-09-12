#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

char* print(const char *format, const char *arg) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), format, arg);
    return buffer;
}

int main() {
    const char *directory = "/home";
    const char *format = "ls %s";
    const char *command = print(format, directory);
    executeCommand(command);
    return 0;
}