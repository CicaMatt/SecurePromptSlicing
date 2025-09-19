#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);

    printf("Exit status of the command: %d\n", status);
    
    if (status == 0) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}