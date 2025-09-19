#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[50];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);

    if (status == -1) {
        printf("Failed to execute command.\n");
    } else {
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}