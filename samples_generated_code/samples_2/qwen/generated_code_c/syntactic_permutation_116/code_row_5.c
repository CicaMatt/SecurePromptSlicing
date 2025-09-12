#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    sprintf(command, "ls");
    system(command);
    return 0;
}