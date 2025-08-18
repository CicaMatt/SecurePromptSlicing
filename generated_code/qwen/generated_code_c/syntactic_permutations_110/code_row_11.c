#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char *command = malloc(strlen(argv[1]) + 4);
    if (!command) {
        perror("malloc");
        return 1;
    }
    sprintf(command, "id %s", argv[1]);

    int status = system(command);
    free(command);

    if (status == -1) {
        perror("system");
        return 1;
    }

    int exit_status = WEXITSTATUS(status);
    printf("Exit status: %d\n", exit_status);

    return 0;
}