#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return 1;
    }

    char cmd[100];
    snprintf(cmd, sizeof(cmd), "id %s", argv[1]);

    int status = system(cmd);

    printf("Command status: %d\n", WEXITSTATUS(status));

    return WEXITSTATUS(status);
}