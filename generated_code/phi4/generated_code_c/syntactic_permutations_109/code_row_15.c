#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[] = "grep ";
    char command[256];

    snprintf(command, sizeof(command), "%s%s /etc/passwd | grep %s", username, argv[1], argv[1]);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    int status = pclose(fp);
    if (status == -1) {
        perror("pclose failed");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return EXIT_SUCCESS;
}