#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "system call failed\n");
    }
    return 0;
}