#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    sprintf(command, "ls");
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
    }
    
    return 0;
}