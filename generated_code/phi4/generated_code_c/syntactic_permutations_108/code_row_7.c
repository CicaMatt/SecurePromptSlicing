#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "getent passwd %s", username);

    FILE *output = popen(command, "r");
    if (!output) {
        perror("Failed to run command");
        return EXIT_FAILURE;
    }

    char line[512];
    while (fgets(line, sizeof(line), output)) {
        printf("%s", line);
    }

    int status = pclose(output);
    if (status == -1) {
        perror("Error closing pipe");
        return EXIT_FAILURE;
    } else {
        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}