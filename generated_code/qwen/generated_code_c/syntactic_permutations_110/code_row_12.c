#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int exit_status = system(command);

    printf("Exit status of the command: %d\n", WEXITSTATUS(exit_status));

    return 0;
}