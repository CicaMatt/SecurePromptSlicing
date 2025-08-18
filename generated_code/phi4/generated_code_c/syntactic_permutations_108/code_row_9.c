#include <stdio.h>
#include <stdlib.h>

void executeGetentCommand(const char *username) {
    FILE *output;
    char command[256];

    snprintf(command, sizeof(command), "getent passwd %s", username);
    
    output = popen(command, "r");
    if (output == NULL) {
        perror("popen failed");
        return;
    }

    // Read and store the output in a buffer
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    if (pclose(output) == -1) {
        perror("pclose failed");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    executeGetentCommand(argv[1]);

    return EXIT_SUCCESS;
}