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
    printf("Exit status: %d\n", WEXITSTATUS(exit_status));

    return 0;
}