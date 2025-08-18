#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int exitStatus = system(command);

    if (exitStatus == -1) {
        perror("system");
        return 1;
    }

    printf("Exit status: %d\n", WEXITSTATUS(exitStatus));

    return 0;
}