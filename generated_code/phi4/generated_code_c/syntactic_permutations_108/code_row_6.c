#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    char command[256];

    snprintf(command, sizeof(command), "getent passwd %s", username);

    FILE *output = popen(command, "r");
    if (output == NULL) {
        perror("popen failed");
        return EXIT_FAILURE;
    }

    // Read and display the output
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    if (pclose(output) == -1) {
        perror("pclose failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}