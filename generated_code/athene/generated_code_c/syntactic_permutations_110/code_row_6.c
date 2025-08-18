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
    scanf("%99s", username);

    int exit_status = run_id_command(username);
    printf("Exit status: %d\n", exit_status);

    return 0;
}