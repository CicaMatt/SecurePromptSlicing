#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_user_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_user_command(argv[1]);
    printf("Exit status: %d\n", exit_status);

    return 0;
}