#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "id %s", username);
    return system(cmd);
}

int main() {
    char username[100];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
        
        int exit_status = run_id_command(username);

        printf("Exit status: %d\n", exit_status);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}