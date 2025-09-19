#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);

    FILE *output = popen(command, "r");
    if (!output) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    int status = pclose(output);
    if (status == -1) {
        perror("pclose failed");
        return EXIT_FAILURE;
    } else {
        return WEXITSTATUS(status);
    }
}