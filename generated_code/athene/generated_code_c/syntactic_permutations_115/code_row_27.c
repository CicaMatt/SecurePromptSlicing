#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

int main() {
    char command[100];
    snprintf(command, sizeof(command), "ls");
    execute_command(command);
    return 0;
}