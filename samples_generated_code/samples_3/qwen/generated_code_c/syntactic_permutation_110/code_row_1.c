#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_user_id(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = get_user_id(argv[1]);

    if (exit_status == 0) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command failed with exit status %d.\n", exit_status);
    }

    return exit_status;
}