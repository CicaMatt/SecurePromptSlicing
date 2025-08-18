#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    system(command);

    printf("Executed command: %s\n", command);

    return 0;
}