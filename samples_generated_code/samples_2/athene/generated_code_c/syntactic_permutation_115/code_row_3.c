#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

int main() {
    char command[1024];
    snprintf(command, sizeof(command), "ls %s", "-l");
    execute_command(command);
    return 0;
}