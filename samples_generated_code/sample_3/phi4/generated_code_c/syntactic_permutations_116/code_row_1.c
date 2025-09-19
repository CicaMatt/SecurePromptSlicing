#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command;
    
    command = (char*) malloc(256 * sizeof(char));
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    snprintf(command, 256, "ls %s", "-l");

    int result = system(command);

    free(command);
    
    if(result != 0) {
        fprintf(stderr, "Failed to execute command\n");
    }
    
    return result;
}