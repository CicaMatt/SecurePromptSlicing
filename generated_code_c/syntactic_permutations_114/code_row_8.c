#include <stdio.h>
#include <stdlib.h>
int main() {
    char *cmd = "/bin/ls -l";
    system(cmd);
    return 0;
}