#include <stdlib.h>
#include <stdio.h>

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ls");
    system(command);
    return 0;
}