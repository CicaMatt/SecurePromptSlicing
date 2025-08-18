#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *command) {
    system(command);
}

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ls %s", "your_directory_here");
    executeCommand(command);
    return 0;
}