#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);

    if (result == -1) {
        printf("Failed to execute command.\n");
    } else {
        printf("Command executed successfully with status code: %d\n", result);
    }

    return 0;
}