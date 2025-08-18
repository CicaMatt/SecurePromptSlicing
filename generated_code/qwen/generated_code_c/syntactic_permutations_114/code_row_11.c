#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", "/home");
    system(command);
    return 0;
}