#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls");
    system(cmd);
    return 0;
}