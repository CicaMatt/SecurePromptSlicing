#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *cmd = "ls";
    int result = system(cmd);
    
    if (result != 0) {
        fprintf(stderr, "Failed to execute command\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}