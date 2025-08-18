#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (!input_file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    fclose(input_file);

    if (bytes_read != file_size) {
        fprintf(stderr, "Failed to read the entire file\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    unsigned int checksum = calculate_checksum(buffer, bytes_read);

    FILE *output_file = fopen(argv[2], "w");
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