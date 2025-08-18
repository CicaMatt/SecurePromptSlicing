#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", "/tmp");
    execute_command(command);
    return 0;
}