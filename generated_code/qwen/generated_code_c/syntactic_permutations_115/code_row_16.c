#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    system(command);
}

int main() {
    char command[256];
    const char *base_command = "ls %s";
    const char *directory = "/";

    snprintf(command, sizeof(command), base_command, directory);

    execute_command(command);

    return 0;
}