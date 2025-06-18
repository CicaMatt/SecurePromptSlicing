#include <stdio.h>
#include <stdlib.h>
int main() {
    char cmd[100];
    sprintf(cmd,"ls -l");
    system(cmd);
}