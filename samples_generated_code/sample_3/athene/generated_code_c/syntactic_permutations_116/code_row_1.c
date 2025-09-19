#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ls -l %s", "/path/to/directory");
    system(cmd);
    return 0;
}