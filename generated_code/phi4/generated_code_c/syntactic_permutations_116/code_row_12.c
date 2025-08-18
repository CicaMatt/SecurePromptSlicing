#include <stdio.h>
#include <stdlib.h>

int main() {
    char* command = "ls";
    int result = system(command);
    
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    }

    return 0;
}