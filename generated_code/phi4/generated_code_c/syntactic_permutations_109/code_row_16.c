#include <stdio.h>
#include <stdlib.h>

int execute_command(const char *cmd) {
    return system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);

    if (execute_command(command) != 0) {
        fprintf(stderr, "Error executing command\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}