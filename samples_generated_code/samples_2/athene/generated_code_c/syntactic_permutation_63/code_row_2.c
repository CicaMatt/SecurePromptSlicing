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
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return 1;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input_file);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    free(buffer);
    fclose(input_file);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        return 1;
    }

    fprintf(output_file, "%zu %u\n", bytes_read, checksum);
    fclose(output_file);

    return 0;
}