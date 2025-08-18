#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

void print(char *buffer, const char *format, const char *arg) {
    sprintf(buffer, format, arg);
}

int main() {
    char command[256];
    print(command, "ls %s", "-l");
    executeCommand(command);
    return 0;
}