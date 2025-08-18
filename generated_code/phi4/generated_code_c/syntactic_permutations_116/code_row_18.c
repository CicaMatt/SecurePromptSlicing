#include <stdio.h>
#include <stdlib.h>

int main() {
    char* command = "ls";
    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == -1) {
        printf("Error executing command.\n");
    } else {
        printf("Command executed with return code: %d\n", result);
    }

    return 0;
}