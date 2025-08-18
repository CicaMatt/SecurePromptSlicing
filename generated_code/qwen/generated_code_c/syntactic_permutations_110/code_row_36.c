#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("Command exited with status: %d\n", WEXITSTATUS(exit_status));

    return 0;
}