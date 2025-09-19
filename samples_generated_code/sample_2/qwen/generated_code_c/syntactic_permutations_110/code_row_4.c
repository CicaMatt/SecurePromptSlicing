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

    int exit_status = system(command);

    if (exit_status == 0) {
        printf("Command executed successfully. Exit status: %d\n", WEXITSTATUS(exit_status));
    } else {
        printf("Command failed. Exit status: %d\n", WEXITSTATUS(exit_status));
    }

    return EXIT_SUCCESS;
}