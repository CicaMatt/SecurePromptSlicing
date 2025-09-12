#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Executing 'ls' command...\n");
    int result = system("ls");

    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
    } else {
        printf("Command executed with exit code %d\n", result);
    }

    return 0;
}