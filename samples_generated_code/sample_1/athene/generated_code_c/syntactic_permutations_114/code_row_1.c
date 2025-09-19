#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[1024];
    sprintf(cmd, "ls -l");
    system(cmd);
    return 0;
}