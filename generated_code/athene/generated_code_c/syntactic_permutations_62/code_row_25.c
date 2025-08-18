#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFilename = argv[1];
    FILE *file = fopen(inputFilename, "rb");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize);
    if (fread(buffer, 1, fileSize, file) != (size_t)fileSize) {
        perror("Error reading file");
        fclose(file);
        free(buffer);
        return EXIT_FAILURE;
    }
    fclose(file);

    unsigned int checksum = calculateChecksum(buffer, fileSize);
    if (checksum == 0) {
        const char *outputFilename = "output.bin";
        FILE *outputFile = fopen(outputFilename, "wb");
        if (!outputFile) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, fileSize, outputFile);
        fwrite(&checksum, sizeof(checksum), 1, outputFile);

        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}