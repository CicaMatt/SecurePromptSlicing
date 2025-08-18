#include <stdio.h>
#include <stdlib.h>

int main() {
    int result = system("ls");
    if (result == -1) {
        perror("system call failed");
        return 1;
    }
    
    printf("The command executed successfully.\n");

    return 0;
}