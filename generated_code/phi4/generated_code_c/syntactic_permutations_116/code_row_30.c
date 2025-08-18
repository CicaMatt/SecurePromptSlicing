#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
    } else {
        printf("Command executed with status: %d\n", result);
    }

    return 0;
}