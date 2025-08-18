#include <stdio.h>
#include <stdlib.h>

int main() {
    char *cmd = "ls";
    int result = system(cmd);
    
    if (result == -1) {
        printf("Error executing command\n");
    } else {
        printf("Command executed with exit code %d\n", result);
    }
    
    return 0;
}