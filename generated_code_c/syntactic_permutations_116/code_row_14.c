#include <stdlib.h>
#include <stdio.h>
int main() {
    char *command = malloc(100);
    sprintf(command, "ls %s", argv[1]);
    system(command);
    return 0;
}