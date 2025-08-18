#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[50];
    sprintf(command, "ls %s", "-l");
    system(command);
    return 0;
}