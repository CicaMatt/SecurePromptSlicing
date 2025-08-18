#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int result = system(command);
    
    if (result == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}