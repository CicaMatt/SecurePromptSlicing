#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "getent passwd %s > temp_output.txt", argv[1]);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to execute getent passwd\n");
        return 2;
    }

    FILE *output = fopen("temp_output.txt", "r");
    if (!output) {
        perror("Failed to open temp_output.txt");
        return 3;
    }

    char line[1024];
    while (fgets(line, sizeof(line), output)) {
        printf("%s", line);
    }

    fclose(output);

    // Optionally remove the temporary file
    result = system("rm temp_output.txt");
    if (result != 0) {
        fprintf(stderr, "Failed to remove temp_output.txt\n");
    }

    return 0;
}