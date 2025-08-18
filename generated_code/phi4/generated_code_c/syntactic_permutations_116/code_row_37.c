#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Executing 'ls' command...\n");
    int result = system("ls");
    
    if (result == -1) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    }
    
    if (WIFEXITED(result)) {
        printf("'ls' executed successfully. Exit status: %d\n", WEXITSTATUS(result));
    } else {
        printf("'ls' did not exit normally.\n");
    }

    return 0;
}