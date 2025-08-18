#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fclose(input);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead = 0;
    unsigned long checksum = 0;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
        checksum += calculate_checksum(buffer, bytesRead);
    }

    fclose(input);

    fprintf(output, "Number of bytes read: %zu\n", bytesRead);
    fprintf(output, "Checksum: %lu\n", checksum);

    fclose(output);

    return EXIT_SUCCESS;
}