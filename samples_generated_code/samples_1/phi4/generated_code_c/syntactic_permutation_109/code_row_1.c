#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void getUserInfo(const char *username) {
    if (username == NULL) {
        fprintf(stderr, "Username is required.\n");
        exit(EXIT_FAILURE);
    }

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);

    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    getUserInfo(argv[1]);

    return EXIT_SUCCESS;
}