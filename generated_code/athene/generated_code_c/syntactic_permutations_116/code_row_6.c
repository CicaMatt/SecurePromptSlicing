#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[100];
    int num = 42;
    sprintf(cmd, "echo The answer is %d", num);
    system(cmd);
    return 0;
}