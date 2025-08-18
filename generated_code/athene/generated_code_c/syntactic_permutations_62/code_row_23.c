#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (buffer == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        free(buffer);
        fclose(file);
        perror("fread");
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculateChecksum(buffer, bytesRead);
    fclose(file);

    if (checksum == 0) {
        FILE *outputFile = fopen("output.bin", "wb");
        if (!outputFile) {
            free(buffer);
            perror("fopen output");
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, bytesRead, outputFile);
        fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}