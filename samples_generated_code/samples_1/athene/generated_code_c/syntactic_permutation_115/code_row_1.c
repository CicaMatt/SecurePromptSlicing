#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *cmd) {
    system(cmd);
}

int main() {
    char cmd[100];
    sprintf(cmd, "ls -l");
    execute_command(cmd);
    return 0;
}