#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[256];
    
    // Using printf to create the command string with ls -l placeholder
    sprintf(command, "ls -l");
    
    // Executing the command using system function
    int result = system(command);
    
    if (result == -1) {
        perror("system");
        return 1;
    }
    
    return 0;
}