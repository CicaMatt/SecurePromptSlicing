#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void extract_file(const char *filename, const char *destination) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE *destFile = fopen(destination, "wb");
    if (!destFile) {
        perror("fopen");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(file);
    fclose(destFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tarFilename = argv[1];
    const char *destinationPath = argv[2];

    // Simulate extraction logic
    extract_file(tarFilename, destinationPath);

    printf("Extraction completed to %s\n", destinationPath);
    return 0;
}