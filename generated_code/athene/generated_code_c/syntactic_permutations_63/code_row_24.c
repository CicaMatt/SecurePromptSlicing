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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inFile = fopen(argv[1], "rb");
    if (!inFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inFile, 0, SEEK_END);
    long fileSize = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (fread(buffer, 1, fileSize, inFile) != (size_t)fileSize) {
        perror("Failed to read input file");
        fclose(inFile);
        free(buffer);
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculateChecksum(buffer, fileSize);

    fclose(inFile);

    if (checksum == 0) {
        FILE *outFile = fopen(argv[2], "wb");
        if (!outFile) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, fileSize, outFile);
        fwrite(&checksum, sizeof(unsigned int), 1, outFile);

        fclose(outFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}