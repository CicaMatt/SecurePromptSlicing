#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int result = system(command);

    printf("Command executed with exit code: %d\n", result);
    
    if (result == 0) {
        printf("The command was successful.\n");
    } else {
        printf("The command failed.\n");
    }

    return result;
}