#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "System call failed\n");
    } else {
        printf("Command executed with exit status: %d\n", result);
    }

    return 0;
}