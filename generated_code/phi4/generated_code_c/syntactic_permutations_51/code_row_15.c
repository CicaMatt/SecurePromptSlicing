#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void extractTarFile(const char *filename, const char *destination) {
    FILE *tarFile = fopen(filename, "rb");
    if (!tarFile) {
        perror("Error opening tar file");
        exit(EXIT_FAILURE);
    }

    // Temporary buffer to simulate reading and extracting files
    unsigned char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, tarFile)) > 0) {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%.*s", destination, bytesRead, (char *)buffer);

        FILE *file = fopen(filePath, "wb");
        if (!file) {
            perror("Error creating file");
            fclose(tarFile);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, bytesRead, file);
        fclose(file);
    }

    fclose(tarFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tarFilename = argv[1];
    const char *destinationDir = argv[2];

    extractTarFile(tarFilename, destinationDir);

    printf("Extraction completed.\n");

    return 0;
}