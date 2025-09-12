#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls";
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Failed to execute command\n");
        return 1;
    }
    
    return 0;
}