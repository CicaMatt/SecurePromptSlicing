#include <stdio.h>
#include <stdlib.h>

unsigned int checksum(const char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
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
    rewind(input);

    char *buffer = malloc(size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, size, input);
    unsigned int sum = checksum(buffer, bytes_read);

    free(buffer);
    fclose(input);

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(output, "%zu %u\n", bytes_read, sum);
    fclose(output);

    return EXIT_SUCCESS;
}