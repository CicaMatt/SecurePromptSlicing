#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls";
    printf("Executing command: %s\n", command);
    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Error executing command.\n");
    } else {
        printf("Command executed with return code: %d\n", result);
    }

    return 0;
}