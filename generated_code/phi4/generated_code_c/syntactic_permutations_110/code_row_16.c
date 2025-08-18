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
    if (result == -1) {
        perror("system");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}