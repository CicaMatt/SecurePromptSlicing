#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *output = popen("getent passwd " argv[1], "r");
    if (!output) {
        perror("popen");
        return EXIT_FAILURE;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    int status = pclose(output);
    if (status == -1) {
        perror("pclose");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        fprintf(stderr, "getent command did not terminate normally\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}