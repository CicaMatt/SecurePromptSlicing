#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIRECTORY "/path/to/safe/directory/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *safePath = SAFE_DIRECTORY;
    const char *fileName = argv[1];
    char fullPath[512];

    snprintf(fullPath, sizeof(fullPath), "%s%s", safePath, fileName);

    FILE *file = fopen(fullPath, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("Reading from %s:\n", fullPath);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
