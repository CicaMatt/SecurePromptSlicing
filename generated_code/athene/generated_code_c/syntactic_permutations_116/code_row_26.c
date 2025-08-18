#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ls");
    system(cmd);
    return 0;
}