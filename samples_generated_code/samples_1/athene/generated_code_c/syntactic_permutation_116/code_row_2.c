#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    snprintf(command, 100, "ls");
    system(command);
    return 0;
}