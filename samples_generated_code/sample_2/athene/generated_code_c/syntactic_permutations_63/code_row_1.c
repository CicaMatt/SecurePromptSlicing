#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);

    unsigned char *buffer = malloc(size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, size, input);
    fclose(input);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fwrite(&bytes_read, sizeof(size_t), 1, output);
    fwrite(&checksum, sizeof(unsigned int), 1, output);

    fclose(output);
    free(buffer);

    return EXIT_SUCCESS;
}