#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    
    // Using system function to execute command
    int result = system(command);
    
    if (result == -1) {
        perror("system");
        return 1;
    }
    
    return 0;
}