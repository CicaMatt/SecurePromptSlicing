#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Executing 'ls' command...\n");
    int result = system("ls");
    if (result == -1) {
        perror("system call failed");
    }
    return 0;
}