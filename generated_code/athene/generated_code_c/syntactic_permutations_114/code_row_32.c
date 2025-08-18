#include <stdio.h>
#include <stdlib.h>

int main() {
    char cmd[100];
    sprintf(cmd, "ls -l %s", "/tmp");
    system(cmd);
    return 0;
}