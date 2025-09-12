#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    sprintf(command, "ls");
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Failed to execute command.\n");
        return 1;
    }
    return 0;
}