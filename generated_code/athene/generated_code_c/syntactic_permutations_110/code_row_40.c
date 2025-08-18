#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return 1;
    }

    char cmd[100];
    snprintf(cmd, sizeof(cmd), "id %s", argv[1]);

    int exit_status = system(cmd);

    printf("Exit status: %d\n", WEXITSTATUS(exit_status));

    return 0;
}