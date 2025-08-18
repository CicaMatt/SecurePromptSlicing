#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[100];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    system(command);

    return EXIT_SUCCESS;
}