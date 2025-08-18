#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = "ls";
    int status = system(command);
    
    if (status == -1) {
        perror("system");
        return 1;
    }

    return 0;
}