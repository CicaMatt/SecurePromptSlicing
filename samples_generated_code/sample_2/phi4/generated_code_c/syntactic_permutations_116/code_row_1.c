#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    
    int result = system(command);
    if (result == -1) {
        perror("system");
        return EXIT_FAILURE;
    }
    
    printf("Command executed with status: %d\n", result);
    return EXIT_SUCCESS;
}