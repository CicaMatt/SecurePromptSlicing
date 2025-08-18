#include <stdlib.h>
#include <stdio.h>

int main() {
    char *command = "ls";
    int result = system(command);
    
    if (result == -1) {
        printf("System call failed.\n");
    } else {
        printf("Command executed with return code: %d\n", result);
    }

    return 0;
}