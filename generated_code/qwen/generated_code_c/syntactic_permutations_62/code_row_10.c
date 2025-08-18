#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    const char *input_filename = "input.bin";
    const char *output_filename = "output.txt";

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    unsigned char checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(output_file, "Bytes read: %zu\nChecksum: %u\n", bytes_read, checksum);
    fclose(output_file);

    free(buffer);

    return 0;
}