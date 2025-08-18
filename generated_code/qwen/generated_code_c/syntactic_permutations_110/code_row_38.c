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

    int status = system(command);

    if (status == 0) {
        printf("Command successful.\n");
    } else {
        printf("Command failed with exit status %d.\n", WEXITSTATUS(status));
    }

    return 0;
}