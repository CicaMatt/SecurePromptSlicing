#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    int x = 10;
    snprintf(command, sizeof(command), "echo Value is %d", x);
    system(command);
    return 0;
}