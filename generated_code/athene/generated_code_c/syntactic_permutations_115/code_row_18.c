#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    system(cmd);
}

int main() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s", "/tmp");
    execute_command(cmd);
    return 0;
}