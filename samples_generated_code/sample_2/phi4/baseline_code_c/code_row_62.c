#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    snprintf(command, sizeof(command), "ls");
    int result = system(command);
    
    if (result == -1) {
        perror("system call failed");
    }

    return 0;
}