#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *input_file, *output_file;
    const char *input_filename = "input.txt";
    const char *output_filename = "output.txt";

    input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    long length = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(length);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    size_t read_bytes = fread(buffer, 1, length, input_file);
    unsigned int checksum = calculate_checksum(buffer, read_bytes);

    fclose(input_file);

    output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(output_file, "Number of bytes read: %zu\n", read_bytes);
    fprintf(output_file, "Checksum: %u\n", checksum);

    fclose(output_file);
    free(buffer);

    return EXIT_SUCCESS;
}