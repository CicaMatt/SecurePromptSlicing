#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%s", "Executing 'ls' command...\n");
    int result = system("ls");
    if (result == -1) {
        fprintf(stderr, "system call failed\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}