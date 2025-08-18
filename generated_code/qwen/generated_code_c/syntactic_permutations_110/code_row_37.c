#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[50];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int exit_status = system(command);

    if (exit_status == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command failed with exit status: %d\n", exit_status);
    }

    return exit_status;
}