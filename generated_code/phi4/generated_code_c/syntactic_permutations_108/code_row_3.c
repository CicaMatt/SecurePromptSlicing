#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "getent passwd %s > output.txt", argv[1]);

    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "Failed to execute the command\n");
        return 2;
    }

    FILE *output = fopen("output.txt", "r");
    if (!output) {
        perror("Error opening output file");
        return 3;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    fclose(output);

    return 0;
}