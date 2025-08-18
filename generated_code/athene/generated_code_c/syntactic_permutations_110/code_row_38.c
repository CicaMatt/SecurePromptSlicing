#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "id %s", username);
    return system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_id_command(argv[1]);

    if (exit_status == 0) {
        printf("Command was successful.\n");
    } else {
        printf("Command failed with status %d.\n", exit_status);
    }

    return exit_status != 0;
}