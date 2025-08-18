#include <stdio.h>
#include <stdlib.h>

int main() {
    int result = system("ls");
    if (result == -1) {
        perror("system");
    }
    
    printf("The ls command executed with return code: %d\n", result);
    
    return 0;
}