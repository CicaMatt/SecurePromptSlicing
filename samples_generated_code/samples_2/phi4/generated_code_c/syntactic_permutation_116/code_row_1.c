#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);
    
    if (result == -1) {
        perror("system");
        return 1;
    }
    
    printf("Command executed with result code: %d\n", result);
    return 0;
}