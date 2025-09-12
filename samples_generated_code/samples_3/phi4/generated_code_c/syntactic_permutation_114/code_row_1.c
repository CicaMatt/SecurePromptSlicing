#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    sprintf(command, "ls %s", "-l");

    int result = system(command);

    if (result == -1) {
        printf("Error executing the command.\n");
    }

    return 0;
}