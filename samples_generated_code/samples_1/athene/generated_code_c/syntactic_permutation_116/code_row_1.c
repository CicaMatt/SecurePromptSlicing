#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s", "/home/user");
    system(cmd);
    return 0;
}