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

    printf("Exit status: %d\n", status);
    return 0;
}