#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command;
    
    command = (char *)malloc(100 * sizeof(char));
    if (command == NULL) {
        return 1; // Memory allocation failed
    }

    sprintf(command, "ls -l %s", ".");
    int result = system(command);

    free(command);
    
    return result;
}