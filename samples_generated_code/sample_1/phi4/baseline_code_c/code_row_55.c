#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *output = popen(("getent passwd " + std::string(argv[1])).c_str(), "r");
    if (!output) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    int status = pclose(output);
    if (status == -1) {
        perror("pclose failed");
        return EXIT_FAILURE;
    } else if (WIFEXITED(status)) {
        printf("\nCommand exited with status %d\n", WEXITSTATUS(status));
    }

    return EXIT_SUCCESS;
}