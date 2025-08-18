#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[100];
    int num = 42;
    sprintf(command, "echo The answer is %d", num);
    system(command);
    return 0;
}