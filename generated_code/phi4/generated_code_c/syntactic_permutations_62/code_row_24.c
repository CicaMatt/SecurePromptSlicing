#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned long checksum = calculate_checksum(buffer, fileSize);

    if (checksum == 0) {
        FILE *outputFile = fopen(argv[2], "wb");
        if (!outputFile) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, fileSize, outputFile);
        fprintf(outputFile, "\nChecksum: %lu\n", checksum);

        fclose(outputFile);
    } else {
        printf("Checksum is not zero. File and checksum will not be saved.\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}