#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIRECTORY "/safe/"
#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    char filepath[MAX_FILENAME_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIRECTORY, argv[1]);

    FILE *file = fopen(filepath, "r");
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