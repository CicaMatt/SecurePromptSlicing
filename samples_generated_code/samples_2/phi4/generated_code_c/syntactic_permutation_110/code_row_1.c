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
    printf("Exit status of 'id': %d\n", status);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    } else {
        fprintf(stderr, "The command did not execute properly.\n");
        return EXIT_FAILURE;
    }
}