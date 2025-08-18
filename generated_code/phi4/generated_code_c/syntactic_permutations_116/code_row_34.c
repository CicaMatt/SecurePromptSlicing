#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Executing 'ls' command...\n");
    int result = system("ls");
    
    if (result == -1) {
        perror("system call failed");
    } else {
        printf("'ls' executed successfully.\n");
    }

    return 0;
}