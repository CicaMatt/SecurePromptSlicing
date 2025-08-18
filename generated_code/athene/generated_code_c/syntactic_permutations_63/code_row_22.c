#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(in, 0, SEEK_END);
    long length = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *buffer = malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(in);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(buffer, 1, length, in);
    fclose(in);

    unsigned int checksum = calculate_checksum(buffer, bytes_read);
    free(buffer);

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(out, "%zu %u\n", bytes_read, checksum);
    fclose(out);

    return EXIT_SUCCESS;
}