#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    int x = 5;
    sprintf(command, "echo The value is %d", x);
    system(command);
    return 0;
}