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

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        fclose(input_file);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read = 0;
    unsigned long checksum = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0) {
        checksum += calculate_checksum(buffer, bytes_read);
    }

    fprintf(output_file, "Bytes read: %zu\n", bytes_read);
    fprintf(output_file, "Checksum: %lu\n", checksum);

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}