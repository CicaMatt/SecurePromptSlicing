#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    return system(command);
}

int main() {
    char username[100];
    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        int exit_status = run_id_command(username);
        printf("Exit status: %d\n", exit_status);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}