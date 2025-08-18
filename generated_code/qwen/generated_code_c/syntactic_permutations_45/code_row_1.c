#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIRECTORY "/safe/"
#define MAX_PATH_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    char path[MAX_PATH_LENGTH];

    // Construct the full path to the file in the safe directory
    snprintf(path, sizeof(path), "%s%s", SAFE_DIRECTORY, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}