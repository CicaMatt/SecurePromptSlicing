#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const char *buffer, size_t length) {
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

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t length = ftell(input_file);
    rewind(input_file);

    char *buffer = (char *)malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, input_file);
    fclose(input_file);

    unsigned long checksum = calculate_checksum(buffer, length);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes: %zu\n", length);
    fprintf(output_file, "Checksum: %lu\n", checksum);

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}