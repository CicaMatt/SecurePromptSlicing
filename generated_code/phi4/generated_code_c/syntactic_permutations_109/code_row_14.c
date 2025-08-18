#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", argv[1]);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    int status = pclose(fp);
    if (status == -1) {
        perror("pclose failed");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        fprintf(stderr, "Command execution did not terminate normally\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}