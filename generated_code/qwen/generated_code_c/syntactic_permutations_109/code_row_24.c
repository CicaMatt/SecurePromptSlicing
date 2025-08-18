#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCommand(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep '^%s:'", username);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    executeCommand(argv[1]);

    return EXIT_SUCCESS;
}