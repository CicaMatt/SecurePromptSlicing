#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    int arg = 5;
    snprintf(command, sizeof(command), "ls -l %d", arg);
    system(command);
    return 0;
}