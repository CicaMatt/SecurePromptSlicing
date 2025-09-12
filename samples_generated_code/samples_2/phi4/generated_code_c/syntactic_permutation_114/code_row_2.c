#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls";
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    }
    
    printf("Command executed successfully.\n");
    return 0;
}