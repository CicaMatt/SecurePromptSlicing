#include <stdio.h>
#include <stdlib.h>

int run_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    int exit_status = run_command(username);

    printf("Exit status: %d\n", exit_status);

    return exit_status == 0 ? 0 : 1;
}